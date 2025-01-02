import torch
import cv2
import time
import threading
from ultralytics import YOLO
from imutils.video import FPS

# Input your YOLO model path here
model_path = "/Users/aa/runs/detect/model_ftc_13/weights/last.pt"  # Replace with your model path

# Load the YOLO model (nano for speed)
model = YOLO(model_path)

# Open the camera
cap = cv2.VideoCapture(0, cv2.CAP_AVFOUNDATION)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)  # Adjust resolution as needed
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FPS, 60)  # Request high FPS

if not cap.isOpened():
    print("Unable to open camera.")
    exit()

# Global variables
frame = None
stop_flag = False
processed_frame = None  # Store the last processed frame

# Known parameters
KNOWN_WIDTHS = [3.81, 8.89]  # Widths of the object in cm
FOCAL_LENGTH = 270  # Initialize focal length

# Initialize a list to store focal length estimates
focal_length_estimates = []

# Set a fixed focal length for testing
FIXED_FOCAL_LENGTH = 300  # Example value, adjust based on your camera calibration

# Define the actual width of the object in cm
ACTUAL_WIDTHS_CM = [3.81, 8.89]  # Example widths of the red object in cm

def calculate_distance(width_in_image, known_width, focal_length):
    if width_in_image == 0 or focal_length == 0:
        return float('inf')  # Avoid division by zero
    return (known_width * focal_length) / width_in_image

def estimate_focal_length(known_distance, width_in_image, known_width):
    if width_in_image == 0:
        return float('inf')  # Avoid division by zero
    return (known_distance * width_in_image) / known_width

# Function to calculate distance based on pixel width and actual width
def calculate_distance_from_pixels(pixel_width, actual_width, focal_length):
    if pixel_width == 0 or focal_length == 0:
        return float('inf')  # Avoid division by zero
    return (actual_width * focal_length) / pixel_width

# Asynchronous frame capture thread
def camera_capture():
    global frame, stop_flag
    while not stop_flag:
        ret, temp_frame = cap.read()
        if ret:
            frame = temp_frame

# Start the camera capture thread
capture_thread = threading.Thread(target=camera_capture)
capture_thread.start()

# Start FPS counter
fps_counter = FPS().start()

try:
    skip_frames = 2  # Process every Nth frame for higher FPS
    frame_count = 0

    while True:
        if frame is not None:
            frame_count += 1

            # Process every Nth frame only (skip rendering others)
            if frame_count % skip_frames == 0:
                start_time = time.time()

                # Resize frame for faster processing
                small_frame = cv2.resize(frame, (320, 240))

                # Run YOLO inference
                results = model(small_frame, verbose=False)
                processed_frame = results[0].plot()

                # Calculate distance for detected objects
                for result in results[0].boxes:
                    width_in_image = result.xywh[0][2]  # Width of the detected object in pixels
                    confidence = result.conf[0]  # Confidence score
                    class_id = int(result.cls[0])  # Class ID
                    class_label = model.names[class_id]  # Get class label from model

                    # If focal length is not set, estimate it using detected objects
                    if FOCAL_LENGTH is None:
                        focal_length_estimate = estimate_focal_length(1.0, width_in_image, KNOWN_WIDTHS[0] / 100)  # Use a default known distance for estimation
                        focal_length_estimates.append(focal_length_estimate)

                        # Average the focal length estimates
                        FOCAL_LENGTH = sum(focal_length_estimates) / len(focal_length_estimates)

                    # Calculate distance using pixel width and actual width
                    if class_label == "red":  # Assuming "red" is the class label for the object
                        actual_width = ACTUAL_WIDTHS_CM[0] / 100  # Convert cm to meters
                    else:
                        actual_width = ACTUAL_WIDTHS_CM[1] / 100  # Convert cm to meters

                    distance = calculate_distance_from_pixels(width_in_image, actual_width, FOCAL_LENGTH)  # Calculate distance using pixel width and actual width
                    print(f"Detected object: {class_label} (Confidence: {confidence:.2f}) - Distance: {distance:.2f} meters")

                # Calculate FPS
                fps = 1 / (time.time() - start_time)
                print(f"Inference FPS: {fps:.2f}")
                fps_counter.update()

            # Display the last processed frame (if available)
            if processed_frame is not None:
                cv2.imshow("YOLOv8 Camera Feed", processed_frame)

            # Exit on 'q' key press
            if cv2.waitKey(1) & 0xFF == ord('q'):
                stop_flag = True
                break

finally:
    # Stop FPS counter and display final stats
    fps_counter.stop()
    print(f"Elapsed time: {fps_counter.elapsed():.2f} seconds")
    print(f"Approx. FPS: {fps_counter.fps():.2f}")

    # Release resources
    capture_thread.join()
    cap.release()
    cv2.destroyAllWindows()