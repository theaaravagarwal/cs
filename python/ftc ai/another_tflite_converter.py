from ultralytics import YOLO
import tensorflow as tf
import os

def convert_yolov8_to_tflite(yolo_model_path, tflite_output_path):
    """
    Converts a YOLOv8 model to a TensorFlow Lite model.

    :param yolo_model_path: Path to the YOLOv8 model file (e.g., .pt file).
    :param tflite_output_path: Path to save the converted TFLite model.
    """
    try:
        # Step 1: Load the YOLOv8 model
        print("Loading YOLOv8 model...")
        model = YOLO(yolo_model_path)

        # Step 2: Export the model to TensorFlow SavedModel format
        print("Exporting to TensorFlow SavedModel format...")
        model.export(format="saved_model", imgsz=640)  # Adjust imgsz as per your model training

        # Step 3: Locate the exported SavedModel directory
        runs_dir = os.path.join(os.getcwd(), 'runs', 'detect')
        print(f"Searching for SavedModel in: {runs_dir}")
        export_dir = None
        for root, dirs, files in os.walk(runs_dir):
            print(f"Checking directory: {root}")
            if "saved_model.pb" in files:
                export_dir = root
                break

        if export_dir is None:
            raise FileNotFoundError("SavedModel not found in the export directory.")

        print(f"SavedModel located at: {export_dir}")

        # Step 4: Convert the TensorFlow SavedModel to TFLite
        print("Converting TensorFlow SavedModel to TensorFlow Lite...")
        converter = tf.lite.TFLiteConverter.from_saved_model(export_dir)
        tflite_model = converter.convert()

        # Step 5: Save the TFLite model
        os.makedirs(os.path.dirname(tflite_output_path), exist_ok=True)
        with open(tflite_output_path, "wb") as f:
            f.write(tflite_model)

        print(f"Conversion complete! TFLite model saved at: {tflite_output_path}")

    except Exception as e:
        print(f"Error: {str(e)}")

if __name__ == "__main__":
    # Specify the path to your YOLOv8 model and desired TFLite output path
    yolo_model_path = "/Users/aa/runs/detect/model_ftc_13/weights/last.pt"  # Replace with your YOLOv8 model file path
    tflite_output_path = "/Users/aa/runs/detect/model_ftc_13/weights/model_last.tflite"  # Replace with your desired TFLite model output path

    convert_yolov8_to_tflite(yolo_model_path, tflite_output_path)