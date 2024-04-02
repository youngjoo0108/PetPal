from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package = 'server_communicator',
            node_executable = 'data_publisher',
            node_name = 'data_publisher',
            output = 'screen',
        ),
        # Node(
        #     package = 'server_communicator',
        #     node_executable = 'log_publisher',
        #     node_name = 'log_publisher',
        #     output = 'screen' ,
        # ),
        Node(
            package = 'server_communicator',
            node_executable = 'server_recive',
            node_name = 'server_recive',
        ),
        Node(
            package = 'server_communicator',
            node_executable = 'data_classify',
            node_name = 'data_classify',
        ),
    ])