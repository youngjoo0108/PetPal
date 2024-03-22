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
        Node(
            package = 'test_209',
            node_executable = 'map',
            node_name = 'map',
            output = 'screen',
        ),
        Node(
            package = 'test_209',
            node_executable = 'astar',
            node_name = 'astar',
            output = 'screen',
        ),
        Node(
            package = 'test_209',
            node_executable = 'astarlocal',
            node_name = 'astarlocal',
        ),
        Node(
            package = 'test_209',
            node_executable = 'route',
            node_name = 'route',
            output = 'screen',
        ),
        Node(
            package = 'test_209',
            node_executable = 'patrol',
            node_name = 'patrol',
            output = 'screen',
        ),
    ])