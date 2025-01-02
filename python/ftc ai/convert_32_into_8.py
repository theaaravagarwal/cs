#this code does not work :(

import tensorflow as tf
import numpy as np
import os

FINALOUTPUTFOLDER = './final_output'

# Initialize converter module
converter = tf.lite.TFLiteConverter.from_saved_model(FINALOUTPUTFOLDER+'/saved_model')
print("initialized converter")
# This enables quantization
converter.optimizations = [tf.lite.Optimize.DEFAULT]
# This ensures that if any ops can't be quantized, the converter throws an error
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS, tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
# For full integer quantization, though supported types defaults to int8 only, we explicitly declare it for clarity.
converter.target_spec.supported_types = [tf.int8]
# These set the input tensors to uint8 and output tensors to float32
converter.inference_input_type = tf.uint8
converter.inference_output_type = tf.float32
print("begin conversion")
tflite_model = converter.convert()
print("conversion complete")

with open(FINALOUTPUTFOLDER+'/limelight_neural_detector_8bit.tflite', 'wb') as f:
  f.write(tflite_model)