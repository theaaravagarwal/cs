from onnx_tf.backend import prepare
import onnx

onnx_model_path = '/Users/aa/runs/detect/model_ftc_13/weights/last.onnx'
tf_model_path = 'model_tf'

onnx_model = onnx.load(onnx_model_path)
tf_rep = prepare(onnx_model)
tf_rep.export_graph(tf_model_path)

print("Model converted successfully.")