from ultralytics import YOLO

# Load a model
model = YOLO("yolov8s.pt")  # load a pretrained model (recommended for training)

# Use the model
model.train(data="my_model_2.yaml", epochs=30, imgsz=320)  # train the model
metrics = model.val()  # evaluate model performance on the validation set


results = model(r'C:\Users\SSAFY\Desktop\Test_YOLO\image_1709624036.jpg', show=True, save=True)  # predict on an image
path = model.export(format="onnx")  # export the model to ONNX format