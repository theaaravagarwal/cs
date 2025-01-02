import cv2
import numpy as np
from ultralytics import YOLO

# Load the YOLO model (ensure this path is correct for your Limelight setup)
model = YOLO("/path/to/your/model.pt")

# Known parameters
ACTUAL_WIDTHS_CM = [3.81, 8.89]  # Example widths of the objects in cm
FOCAL_LENGTH = 300  # Fixed focal length, adjust based on your camera calibration

def calculate_distance(pixel_width, actual_width, focal_length):
    if pixel_width == 0 or focal_length == 0:
        return float('inf')  # Avoid division by zero
    return (actual_width * focal_length) / pixel_width

def draw_boxes_and_info(image, detections, distances):
    for det, dist in zip(detections, distances):
        box = det.xyxy[0].cpu().numpy().astype(int)
        conf = det.conf.item()
        cls = int(det.cls.item())
        label = f"{model.names[cls]} {conf:.2f} {dist:.2f}m"
        cv2.rectangle(image, (box[0], box[1]), (box[2], box[3]), (0, 255, 0), 2)
        cv2.putText(image, label, (box[0], box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    return image

# runPipeline() is called every frame by Limelight's backend.
def runPipeline(image, llrobot):
    # Initialize variables
    largestContour = np.array([[]])
    llpython = [0] * 8  # Initialize with zeros

    # Resize image for faster processing
    small_image = cv2.resize(image, (320, 240))

    # Run YOLO inference
    results = model(small_image, verbose=False)

    if len(results) > 0:
        # Calculate distances and draw boxes
        distances = []
        for det in results[0].boxes:
            width_pixels = det.xywh[0][2].item()
            cls = int(det.cls.item())
            actual_width = ACTUAL_WIDTHS_CM[min(cls, len(ACTUAL_WIDTHS_CM)-1)] / 100  # Convert cm to meters
            distance = calculate_distance(width_pixels, actual_width, FOCAL_LENGTH)
            distances.append(distance)

        # Draw boxes and info on the original image
        image = draw_boxes_and_info(image, results[0].boxes, distances)

        # Find the largest contour (assuming the largest detection is of interest)
        if len(results[0].boxes) > 0:
            largest_det = max(results[0].boxes, key=lambda x: x.xywh[0][2] * x.xywh[0][3])
            box = largest_det.xyxy[0].cpu().numpy().astype(int)
            largestContour = np.array([[box[0], box[1]], [box[2], box[1]], [box[2], box[3]], [box[0], box[3]]])

            # Populate llpython with data from the largest detection
            cls = int(largest_det.cls.item())
            conf = largest_det.conf.item()
            dist = distances[results[0].boxes.index(largest_det)]
            llpython = [cls, conf, dist, box[0], box[1], box[2], box[3], 0]

    # Add a text overlay to the image
    cv2.putText(image, "Limelight YOLO Detection", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    return largestContour, image, llpython