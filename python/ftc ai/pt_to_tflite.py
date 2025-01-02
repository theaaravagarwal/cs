from ultralytics import YOLO
model = YOLO("/Users/aa/runs/detect/model_ftc_13/weights/last.pt")
model.export(format="tflite", int8=True)