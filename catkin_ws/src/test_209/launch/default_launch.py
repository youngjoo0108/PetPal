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
            node_executable = 'purefollow',
            node_name = 'purefollow',
        ),
    ])