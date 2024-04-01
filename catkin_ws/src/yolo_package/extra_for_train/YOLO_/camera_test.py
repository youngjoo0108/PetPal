from ultralytics import YOLO


# Load a model
model = YOLO("yolov8n.pt")  # load a pretrained model (recommended for training)

# Use the model
results = model(source=0, conf=0.4, show=True, save=True)  # predict on an image