from ultralytics import YOLO
model = YOLO('yolov8n.pt')
results = model.train(
    data='/Users/aa/Downloads/SampleDetector.v11i.yolov8 (1)/data.yaml', #local path to training data
    epochs=50,
    imgsz=640,
    batch=16,
    name='model_ftc_thing',
    verbose=True
)
results = model.val()