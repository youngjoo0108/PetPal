from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Node(
        #     package='my_package',
        #     node_namespace='talker',
        #     node_executable='talker',
        #     node_name='screen'
        # ),
        # Node(
        #     package='my_package',
        #     node_namespace='listener',
        #     node_executable='listener',
        #     node_name='screen'
        # ),
        # Node(
        #     package='turtlesim',
        #     node_executable='mimic',
        #     node_name='mimic',
        #     remappings=[
        #         ('/input/pose', '/turtlesim1/turtle1/pose'),
        #         ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
        #     ]
        # ),
        Node(
            package = 'my_package',
            node_executable = 'communication',
            node_name = 'screen',
        ),
        Node(
            package = 'my_package',
            node_executable = 'odom',
            node_name = 'screen',
        ),
        Node(
            package = 'my_package',
            node_executable = 'path',
            node_name = 'screen',
        ),
    ])