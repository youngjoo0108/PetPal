This is for communicate to Server.

We will send the next kind of data.
- Current coordinates
- Change the mode of the robot
- Image of Camera
- Data of Map
- Change the status of IoT device
- Logs
    - Change the status of IoT device
    - Chage the mode of robot
    - Error of the moving
    - Handle Object

We will recive the next kind of data
- User command
- Result of the Image Detection
- Command(from Schedule)
- Object Information on map

Data Publisher.py

It use AMQP Protocol for sending message to RabbitMQ

'''
self.amqp_channel.basic_publish(exchange='',
                               routing_key='log_queue',
                               body=log_message,
                               properties=pika.BasicProperties(
                                   delivery_mode=2,  # 메시지를 영속적으로 만듦
                               ))
'''
교환기(exchange) 유형에 따라 routing_key의 역할과 필요성이 달라집니다. routing_key는 교환기가 메시지를 어떤 큐로 라우팅할지 결정하는 데 사용되며, 교환기의 유형에 따라 그 해석이 달라집니다. 여기서 topic 교환기나 다른 교환기 유형을 사용할 때 routing_key의 역할을 살펴보겠습니다.

Direct Exchange
direct 교환기는 routing_key를 사용하여 메시지를 해당 routing_key와 정확히 일치하는 큐로 라우팅합니다. 따라서, routing_key는 이 경우 필수적입니다.
Topic Exchange
topic 교환기는 routing_key를 더 유연하게 해석합니다. routing_key는 패턴 매칭을 사용하여 메시지를 하나 이상의 큐로 라우팅할 수 있습니다. 예를 들어, *.critical 패턴을 가진 routing_key는 "log.critical"에 일치하지만, "log.info"에는 일치하지 않습니다. 이 경우에도 routing_key는 필수적이지만, 패턴 매칭을 통한 유연한 라우팅을 가능하게 합니다.
Fanout Exchange
fanout 교환기는 routing_key를 무시하고, 교환기에 바인딩된 모든 큐에 메시지를 브로드캐스트합니다. 이 경우, routing_key는 메시지 라우팅에 영향을 주지 않으며, 실제로 메시지를 전송할 때 routing_key를 지정하지 않아도 됩니다(또는 무시됩니다).
Headers Exchange
headers 교환기는 routing_key 대신 메시지 헤더에 기반하여 메시지를 라우팅합니다. 이 유형의 교환기는 메시지 헤더 내의 키-값 쌍을 사용하여 라우팅 결정을 내립니다. headers 교환기를 사용할 때는 routing_key가 필요하지 않으며, 대신 메시지의 헤더 정보가 중요해집니다.
결론적으로, routing_key의 필요성과 역할은 사용하는 교환기의 유형에 따라 달라집니다. direct와 topic 교환기는 routing_key를 사용하여 라우팅 결정을 내리지만, fanout과 headers 교환기는 다른 기준을 사용합니다.
---
pika 라이브러리를 사용하여 RabbitMQ 서버와 통신할 때, RabbitMQ 서버가 로컬이 아니라 http://j10a209.p.ssafy.io:8081와 같은 URL을 가진 원격 서버에 설치되어 있다면, 통신 설정을 그에 맞춰 조정해야 합니다. 그러나, RabbitMQ와의 통신에는 http:// 스키마가 아닌 amqp:// 또는 amqps:// (SSL/TLS 사용 시) 스키마를 사용합니다. URL 형식의 주소는 HTTP/HTTPS 프로토콜을 위한 것이므로, RabbitMQ 서버에 연결하기 위해서는 AMQP 프로토콜을 지원하는 주소 형식을 사용해야 합니다.

RabbitMQ 서버에 연결하기 위해 필요한 정보는 다음과 같습니다:

호스트명: RabbitMQ 서버의 주소입니다. 로컬이 아닌 경우, 해당 서버의 IP 주소나 도메인 이름을 사용합니다.
포트: RabbitMQ 서비스가 실행 중인 포트입니다. 기본적으로 AMQP 프로토콜은 5672 포트를 사용하며, AMQPS의 경우 5671 포트를 사용합니다.
사용자 이름 및 비밀번호: RabbitMQ 서버에 접속하기 위한 인증 정보입니다.
가상 호스트: RabbitMQ에서 사용하는 가상 호스팅 경로입니다. 기본값은 / 입니다.
만약 http://j10a209.p.ssafy.io:8081이 RabbitMQ 서버의 웹 관리 인터페이스를 위한 주소라면, 실제 AMQP 연결 주소는 다를 가능성이 높습니다. 웹 관리 인터페이스와 AMQP 서비스 포트는 일반적으로 다릅니다.

연결 설정 예시
python
Copy code
import pika

# RabbitMQ 서버 접속 정보
amqp_url = 'amqp://user:password@hostname/vhost'

# URL 파싱
url_params = pika.URLParameters(amqp_url)

# 연결 생성
connection = pika.BlockingConnection(url_params)

# 채널 생성
channel = connection.channel()
여기서 amqp_url은 실제 연결 정보를 기반으로 작성해야 합니다. 예를 들어, RabbitMQ 서버의 호스트명이 j10a209.p.ssafy.io이고, 사용자 이름과 비밀번호가 각각 user, password라고 가정하면, AMQP URL은 다음과 같이 될 수 있습니다:

python
Copy code
amqp_url = 'amqp://user:password@j10a209.p.ssafy.io/'
또한, RabbitMQ 서버의 AMQP 서비스 포트가 기본값(5672)이 아닌 경우, 호스트명 뒤에 :포트번호를 추가하여 지정할 수 있습니다. SSL/TLS를 사용하는 경우 amqps:// 스키마를 사용하고, 필요한 SSL 인증서 정보도 함께 제공해야 합니다.

중요한 사항
실제 RabbitMQ 서버에 접속하기 위한 호스트명, 포트, 사용자 이름, 비밀번호, 가상 호스트 등의 정보는 RabbitMQ 서버 관리자에게 문의하여 정확히 파악해야 합니다.
웹 관리 인터페이스 URL과 AMQP 연결 URL은 목적이 다르므로 혼동하지 않도록 주의해야 합니다.