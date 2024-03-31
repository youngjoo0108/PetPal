from setuptools import setup

package_name = 'server_communicator'

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
    maintainer_email='ktb5057@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'server_test = server_communicator.server_test:main',
            'data_subscription = server_communicator.server_recive:main',
            'data_publisher = server_communicator.data_publisher:main',
            'gpu_image_publisher = server_communicator.gpu_image_publisher:main',
            'log_publisher = server_communicator.log_publisher:main',
            'streaming_publisher = server_communicator.streaming_publisher:main',
        ],
    },
)
