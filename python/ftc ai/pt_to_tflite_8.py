import torch
import tensorflow as tf
from tensorflow import keras
from ultralytics import YOLO

# Load the YOLOv8 model architecture
model = YOLO('/Users/aa/runs/detect/model_ftc_13/weights/last.pt')  # Load your custom YOLOv8 model

# Convert YOLOv8 model to ONNX format
dummy_input = torch.randn(1, 3, 640, 640)  # Adjust input size as needed for YOLOv8
onnx_path = 'model.onnx'
torch.onnx.export(model, dummy_input, onnx_path, opset_version=12)

# Load the ONNX model
onnx_model = tf.experimental.onnx.load_model(onnx_path)

# Convert ONNX model to TensorFlow model
tf_model = tf.keras.models.load_model(onnx_model)

# Convert TensorFlow model to TensorFlow Lite model with quantization
converter = tf.lite.TFLiteConverter.from_keras_model(tf_model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]  # Enable default optimizations (including quantization)
tflite_model = converter.convert()

# Save the TensorFlow Lite model
with open('model.tflite', 'wb') as f:
    f.write(tflite_model)

print("Conversion complete: model.tflite")
