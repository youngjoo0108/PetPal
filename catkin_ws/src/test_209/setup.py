from setuptools import setup

package_name = 'test_209'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='SSAFY',
    maintainer_email='ksshc@snu.ac.kr',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # coordinate
            'odom=test_209.odom_node:main',
            'lidar=test_209.lidar_node:main',

            # follow
            'follow=test_209.path_tracking:main',
            'purefollow=test_209.pure_pursuit:main',
            'patrol=test_209.patrol:main',

            # mapping
            'map=test_209.load_map:main',
            'mapping=test_209.make_map:main',
            'setting=test_209.map_setting:main',
            'route=test_209.patrol_route:main',
            'resize=test_209.resize_map:main',

            # path planning
            'dijkstra=test_209.dijkstra:main',
            'astar=test_209.a_star:main',
            'astarlocal=test_209.a_star_local:main',

            # iot control
            'iot=test_209.iot_control:main',
            'handcontrol=test_209.hand_control:main',
            'iot_test=test_209.iot_test:main',
            'iot_room1=test_209.iot_room1:main',

            # dog tracking
            'tracking=test_209.tracking:main',
            'tracking_test=test_209.tracking_test:main',
            
            
            # etc(for test)
            'make=test_209.make_path:main',
            'path=test_209.path_node:main',
            'drive_test=test_209.drive_test:main',
            'odomprint=test_209.odom_print:main',
            'iot_user=test_209.iot_user_input:main',
        ],
    },
)
