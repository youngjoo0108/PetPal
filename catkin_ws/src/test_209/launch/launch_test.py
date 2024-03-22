from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package = 'test_209',
            node_executable = 'odom',
            node_name = 'odom',
            output = 'screen',
        ),
        Node(
            package = 'test_209',
            node_executable = 'lidar',
            node_name = 'lidar',
            output = 'screen',
        ),
        # Node(
        #     package = 'test_209',
        #     node_executable = 'follow',
        #     node_name = 'follow',
        #     output = 'screen',
        # ),
        # Node(
        #     package = 'test_209',
        #     node_executable = 'purefollow',
        #     node_name = 'purefollow',
        #     output = 'screen',
        # ),
        Node(
            package = 'test_209',
            node_executable = 'mapping',
            node_name = 'mapping',
        ),
        Node(
            package = 'test_209',
            node_executable = 'astar',
            node_name = 'astar',
            output = 'screen' ,
        ),
        Node(
            package = 'test_209',
            node_executable = 'astarlocal',
            node_name = 'astarlocal',
        ),
        Node(
            package = 'test_209',
            node_executable = 'iotcontrol',
            node_name = 'iotcontrol',
            output = 'screen' ,
        ),
        # Node(
        #     package = 'test_209',
        #     node_executable = 'odomprint',
        #     node_name = 'odomprint',
        # ),
    ])