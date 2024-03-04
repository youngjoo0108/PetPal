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
            'odom=test_209.odom_node:main',
            'path=test_209.path_node:main',
            'lidar=test_209.lidar_node:main',
            'follow=test_209.path_tracking:main',
            'make=test_209.make_path:main',
            'map=test_209.load_map:main',
            'mapping=test_209.make_map:main',
            'astar=test_209.a_star:main',
            'drive=test_209.drive_test:main',
        ],
    },
)
