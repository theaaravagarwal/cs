from ultralytics import YOLO

# Load the YOLOv8 model
model = YOLO("/Users/aa/runs/detect/model_ftc_13/weights/last.pt")

# Export the model to ONNX format
model.export(format="onnx")