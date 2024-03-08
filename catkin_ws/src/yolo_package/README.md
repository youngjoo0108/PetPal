<img src="https://capsule-render.vercel.app/api?type=wave&color=auto&height=300&section=header&text=YOLO%20object%20detection&fontSize=70" style="width: 100%;">

git ignore test

<h2>Yolo v8 nano ver.1 [2024-03-05]</h2>

- model name : my_model_2
- Epoch : 10
- Dataset(number of images) : 300
- classes(number of class) : 12
<h3>Result</h3>

- Percision : 0.72554
- Recall : 0.64783
- mAP50 : 0.68614
- mAP50-95 : 0.52116
- Processing Time Per Image(OnDevice) : 1.0ms preprocess, 31.0ms inference, 1.0ms postprocess

**첫 테스트 모델로 모델이 학습이 되었다 정도의 수준만 보여줌**


<h2>Yolo v8 nano ver.2 [2024-03-06]</h2>

- model name : my_model_3
- Epoch : **20**
- Dataset(number of images) : 300
- classes(number of class) : 12
<h3>Result</h3>

- Percision : **0.82701**
- Recall : **0.73746**
- mAP50 : **0.82524**
- mAP50-95 : **0.64716**
- Processing Time Per Image(OnDevice) : 0.0ms preprocess, 31.3ms inference, 1.0ms postprocess

**Epoch를 20으로 증가 시킨 결과 모델의 수준이 상당히 올라옴.<br>다만, 데이터셋의 라벨링 분류 누락으로 감지하지 못하는 객체나 테이블의 종류를 3가지로 분류하여 모델이 이의 분류에 혼동을 하는 경우가 있음
<br>가장 치명적인 문제로 작은 물체들(차 키, 지갑, 리모컨)을 혼동하는 이슈가 심함**

<h2>Yolo v8 nano ver.3 [2024-03-06]</h2>

- model name : my_model_v2_1
- Epoch : 20
- Dataset(number of images) : **400**
- classes(number of class) : **16**
<h3>Result</h3>

- Percision : **0.76724**
- Recall : **0.57109**
- mAP50 : **0.57756**
- mAP50-95 : **0.37215**
- Processing Time Per Image(OnDevice) : 1.0ms preprocess, 33.9ms inference, 1.0ms postprocess

**다른 형태나 다른 색깔의 객체를 하나의 클래스로 다시 분류하고.<br>
멀리 떨어져 사람의 눈으로도 구별이 힘든 물체들을 SmallThing으로 분류하고, 사람 눈으로 식별이 가능한 이미지만 정확히 라벨링하여 이들을 식별하는 정밀도와 재현율을 높였다.<br>
다만, 역풍으로 전체적인 정밀도와 재현율은 감소하였다.**


<h2>Yolo v8 nano ver.4 [2024-03-06]</h2>

- model name : my_model_v2_2
- Epoch : **30**
- Dataset(number of images) : 400
- classes(number of class) : 16
<h3>Result</h3>

- Percision : 0.77765
- Recall : **0.62348**
- mAP50 : **0.61579**
- mAP50-95 : 0.39258
- Processing Time Per Image(OnDevice) : 1.0ms preprocess, 32.8ms inference, 0.0ms postprocess

**감소한 정밀도와 재현율을 Epoch를 증가시킴으로 증가시켰다.<br>
다만, 아직 재현율이 0.7 미만으로 운용 가능한 성능은 아니다.**



<h2>Yolo v8 small ver.1 [2024-03-07]</h2>

- model name : my_model_**small**_1
- Epoch : 30
- Dataset(number of images) : 400
- classes(number of class) : 16
<h3>Result</h3>

- Percision : **0.79117**
- Recall : **0.74283**
- mAP50 : **0.7817**
- mAP50-95 : **0.50383**
- Processing Time Per Image(OnDevice) : 1.0ms preprocess, **78.6ms inference**, 1.0ms postprocess


**낮은 성능을 보완하기 위해 기존의 nano 모델이 아닌 한 단계 성능이 높은 small 모델을 사용하였다.<br>
성능은 눈에 띄게 좋아졌으나, 이미지당 처리 시간이 증가하여 평균 11프레임으로 동작이 가능하져서 GPU 서버의 필요성이 나타났다.**


<h2>Yolo v8 medium ver.1 [2024-03-07]</h2>

- model name : my_model_**medium**_1
- Epoch : 30
- Dataset(number of images) : 400
- classes(number of class) : 16
<h3>Result</h3>

- Percision : 0.74838
- Recall : 0.75301
- mAP50 : 0.79077
- mAP50-95 : 0.46745
- Processing Time Per Image(OnDevice) : 1.0ms preprocess, **148.5ms inference**, 1.1ms postprocess

**모델에 따른 성능 비교를 위해 small보다 한 단계 더 높은 medium을 사용하였다.<br>
하지만 처리 시간이 더욱 늘어날 뿐 유의미한 성능 향상은 없었다.**


<h2>Yolo v8 small ver.2 [2024-03-07]</h2>

- model name : my_model_**small**_2
- Epoch : **60**
- Dataset(number of images) : 400
- classes(number of class) : 16
<h3>Result</h3>

- Percision : 0.71919
- Recall : 0.78445
- mAP50 : 0.80152
- mAP50-95 : 0.51579
- Processing Time Per Image(OnDevice) : 

**Epoch의 증가에 따른 성능 향상을 테스트 해보았지만,<br>
best model이 42번째 학습 모델이고, 이전 small ver1과 비교했을때 유의미한 차이는 없었다.**

