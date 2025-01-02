import cv2
import numpy as np
import tensorflow as tf

# Load the TFLite model
try:
    interpreter = tf.lite.Interpreter(model_path="/home/limelight/model.tflite")
    interpreter.allocate_tensors()

    # Get model details
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    input_shape = input_details[0]['shape']

    # Load labels
    labels = ['red', 'blue', 'yellow']
except Exception as e:
    print(f"Error loading model or labels: {e}")
    interpreter = None
    labels = []

def preprocess_image(image, input_shape):
    resized = cv2.resize(image, (input_shape[1], input_shape[2]))
    normalized = resized.astype(np.float32) / 255.0
    return np.expand_dims(normalized, axis=0)

def draw_boxes_and_labels(image, boxes, classes, scores):
    for box, cls, score in zip(boxes, classes, scores):
        y1, x1, y2, x2 = box
        label = f"{labels[cls]}: {score:.2f}"
        cv2.rectangle(image, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
        cv2.putText(image, label, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    return image

# runPipeline() is called every frame by Limelight's backend.
def runPipeline(image, llrobot):
    # Initialize variables
    largestContour = np.array([[]])
    llpython = [0] * 8  # Initialize with zeros

    if interpreter is None:
        cv2.putText(image, "Model not loaded", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        return largestContour, image, llpython

    try:
        # Preprocess the image
        preprocessed_image = preprocess_image(image, input_shape)

        # Set the tensor to point to the input data
        interpreter.set_tensor(input_details[0]['index'], preprocessed_image)

        # Run inference
        interpreter.invoke()

        # Get detection results
        boxes = interpreter.get_tensor(output_details[0]['index'])[0]
        classes = interpreter.get_tensor(output_details[1]['index'])[0]
        scores = interpreter.get_tensor(output_details[2]['index'])[0]

        # Filter out weak detections
        valid_detections = scores > 0.5
        boxes = boxes[valid_detections]
        classes = classes[valid_detections].astype(int)
        scores = scores[valid_detections]

        if len(boxes) > 0:
            # Draw boxes and labels on the image
            image = draw_boxes_and_labels(image, boxes, classes, scores)

            # Find the largest detection
            largest_idx = np.argmax((boxes[:, 2] - boxes[:, 0]) * (boxes[:, 3] - boxes[:, 1]))
            largest_box = boxes[largest_idx]

            # Create contour for the largest detection
            largestContour = np.array([
                [largest_box[1], largest_box[0]],
                [largest_box[3], largest_box[0]],
                [largest_box[3], largest_box[2]],
                [largest_box[1], largest_box[2]]
            ], dtype=np.int32)

            # Populate llpython with data from the largest detection
            llpython = [
                classes[largest_idx],
                scores[largest_idx],
                largest_box[1],  # x1
                largest_box[0],  # y1
                largest_box[3],  # x2
                largest_box[2],  # y2
                0,
                0
            ]

        # Add a text overlay to the image
        cv2.putText(image, "Limelight TFLite Detection", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    except Exception as e:
        cv2.putText(image, f"Error: {str(e)}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

    return largestContour, image, llpython