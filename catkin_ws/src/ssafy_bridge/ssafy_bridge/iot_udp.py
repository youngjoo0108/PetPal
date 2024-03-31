
import rclpy
from rclpy.node import Node  
import time
import os
import socket
import threading
import struct
import binascii
from ssafy_msgs.msg import IotInfo

params_status = {
    (0xa,0x25 ) : ("IDLE", 0),
    (0xb,0x31 ) : ("CONNECTION", 1),
    (0xc,0x51) : ("CONNECTION_LOST", 2),
    (0xb,0x37) : ("ON", 0),
    (0xa,0x70) : ("OFF", 1),
    (0xc,0x44) : ("ERROR", 2)
}

params_control_cmd= {
    "TRY_TO_CONNECT" : (0xb,0x31 )  ,
    "SWITCH_ON" : (0xb,0x37 ) ,
    "SWITCH_OFF" : (0xa,0x70),
    "RESET" : (0xb,0x25) ,
    "DISCONNECT" : (0x00,0x25)
}

class iot_udp(Node):

    def __init__(self):
        super().__init__('iot_udp')

        self.iot_pub = self.create_publisher(IotInfo, 'iot', 10)

        self.ip='127.0.0.1'
        self.port=7502
        self.send_port=7401

        # 로직 1. 통신 소켓 생성
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        recv_address = (self.ip,self.port)
        self.sock.bind(recv_address)
        self.data_size=65535
        self.now_device = None
        
        # 로직 2. 멀티스레드를 이용한 데이터 수신
        thread = threading.Thread(target=self.recv_udp_data)
        thread.daemon = True 
        thread.start() 

        self.is_recv_data=False

    def data_parsing(self,raw_data) :
        # print(raw_data)
        # 로직 3. 수신 데이터 파싱

        header=raw_data[0:19].decode()
        data_length=struct.unpack('i',raw_data[19:23])
        # aux_data=?

        if header == '#Appliances-Status$' and data_length[0] == 20:

            uid_pack=struct.unpack('16B',raw_data[35:35+16])
            uid=self.packet_to_uid(uid_pack)

            if self.now_device and self.now_device != uid:
                return
        
            network_status=params_status[struct.unpack('2B',raw_data[35+16:35+18])][1]
            device_status=params_status[struct.unpack('2B',raw_data[35+18:35+20])][1]
            
            self.is_recv_data=True
            self.recv_data=[uid,network_status,device_status]
 
    def send_data(self,uid,cmd):
        
        # 로직 4. 데이터 송신 함수 생성

        header='#Ctrl-Command$'.encode()
        data_length=struct.pack('i',18)
        aux_data=struct.pack('iii',0,0,0)
        self.upper=header+data_length+aux_data
        self.tail='\r\n'.encode()

        uid_pack=self.uid_to_packet(uid)
        cmd_pack=bytes([cmd[0],cmd[1]])

        send_data=self.upper+uid_pack+cmd_pack+self.tail
        self.sock.sendto(send_data,(self.ip,self.send_port))

    def recv_udp_data(self):
        while True :
            raw_data, sender = self.sock.recvfrom(self.data_size)
            self.data_parsing(raw_data)

            msg = IotInfo()
            msg.uid = self.recv_data[0]
            msg.network = self.recv_data[1]
            msg.state = self.recv_data[2]

            self.iot_pub.publish(msg)


    def uid_to_packet(self,uid):
        uid_pack=binascii.unhexlify(uid)
        return uid_pack

        
    def packet_to_uid(self,packet):
        uid=""
        for data in packet:
            if len(hex(data)[2:4])==1:
                uid+="0"
            
            uid+=hex(data)[2:4]
            
        return uid


    def scan(self):
        
        print('SCANNING NOW.....')
        print('BACK TO MENU : Ctrl+ C')
        # 로직 6. iot scan

        # 주변에 들어오는 iot 데이터(uid,network status, device status)를 출력하세요.
        if self.is_recv_data==True :
            print('UID = {0}'.format(self.recv_data[0]))
            print('network = {0}'.format(self.recv_data[1]))
            print('status = {0}'.format(self.recv_data[2]))
        else:
            print('No Device...')
        
                   

    def connect(self, uid):
        # 로직 7. iot connect

        # iot 네트워크 상태를 확인하고, CONNECTION_LOST 상태이면, RESET 명령을 보내고,
        # 나머지 상태일 때는 TRY_TO_CONNECT 명령을 보내서 iot에 접속하세요.
        if self.is_recv_data==True:
            if self.recv_data[1] == 2:
                self.send_data(uid,params_control_cmd['RESET'])
            else:
                self.send_data(uid,params_control_cmd['TRY_TO_CONNECT'])

    
    def control(self, uid):
        # 로직 8. iot control
        
        # iot 디바이스 상태를 확인하고, ON 상태이면 OFF 명령을 보내고, OFF 상태면 ON 명령을 보내서,
        # 현재 상태를 토글시켜주세요.
        if self.is_recv_data==True:
            if self.recv_data[2] == 0:
                self.send_data(uid,params_control_cmd["SWITCH_OFF"])
            elif self.recv_data[2] == 1:
                self.send_data(uid,params_control_cmd["SWITCH_ON"])


    def disconnect(self, uid):
        if self.is_recv_data==True :
            self.send_data(uid,params_control_cmd["DISCONNECT"])
        

    def all_procedures(self, uid):
        self.now_device = uid
        while True:
            if self.recv_data[1] == 1:
                break
            self.connect(uid)

        time.sleep(0.5)
        temp = self.recv_data[2]
        
        while True:
            if self.recv_data[2] != temp:
                break
            self.control(uid)

        time.sleep(0.5)

        while True:
            if self.recv_data[1] == 0:
                break
            self.disconnect(uid)

        self.now_device = None


    def __del__(self):
        self.sock.close()
        print('del')


def main(args=None):
    rclpy.init(args=args)
    iot = iot_udp()
    rclpy.spin(iot)
    iot.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()