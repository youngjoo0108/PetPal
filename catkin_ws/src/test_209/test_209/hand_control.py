import rclpy, time
from rclpy.node import Node
import os, time
from ssafy_msgs.msg import TurtlebotStatus,HandControl


class Handcontrol(Node):

    def __init__(self):
        super().__init__('hand_control')
                
        self.hand_control_pub = self.create_publisher(HandControl, '/hand_control', 10)                
        self.turtlebot_status = self.create_subscription(TurtlebotStatus,'/turtlebot_status',self.turtlebot_status_cb,10)

        self.hand_control_msg=HandControl()        
        self.turtlebot_status_msg = TurtlebotStatus()
        
        self.is_turtlebot_status = False
        

    def hand_control_status(self):

        if self.is_turtlebot_status:
            print(f"Turtlebot Status - can_lift: {self.turtlebot_status_msg.can_lift}, put: {self.turtlebot_status_msg.can_put}, is_lifted: {self.turtlebot_status_msg.can_use_hand}")
        else:
            print("Turtlebot status is not yet received.")

    def hand_control_preview(self):

        self.hand_control_msg.control_mode = 1 
        self.hand_control_pub.publish(self.hand_control_msg)

        print("Hand control preview mode activated.")

    def hand_control_pick_up(self):

        self.hand_control_msg.control_mode = 2  
        self.hand_control_msg.put_distance = 1.0
        self.hand_control_msg.put_height = 0.0
        self.hand_control_pub.publish(self.hand_control_msg)
            
        print("Hand control pick-up mode activated.")
        

    def hand_control_put_down(self):

        self.hand_control_msg.control_mode = 3  
        self.hand_control_msg.put_distance = 1.0
        self.hand_control_msg.put_height = 0.5
        self.hand_control_pub.publish(self.hand_control_msg)
        print("Hand control put-down mode activated.")
        

    def turtlebot_status_cb(self,msg):

        self.is_turtlebot_status=True
        self.turtlebot_status_msg=msg

        print('Select Menu [0: status_check, 1: preview, 2:pick_up, 3:put_down')
        menu=input(">>")

        print(menu)
        if menu=='0' :
            self.hand_control_status()
            
        if menu=='1' :
            self.hand_control_preview()
                           
        if menu=='2' :
            self.hand_control_pick_up()

        if menu=='3' :
            self.hand_control_put_down()
        

def main(args=None):
    rclpy.init(args=args)
    sub1_hand_control = Handcontrol()    
    rclpy.spin(sub1_hand_control)
    sub1_hand_control.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()