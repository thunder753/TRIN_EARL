Current developers: Jin Pyo Jeon (jinpyojeon@trincoll.edu), Basileal Imana (basileal.imana@trincoll.edu), Barok Imana (Barok.imana@trincoll.edu)
Previous developers: Mike Castellana

Note that this file is formatted as Github flavored markdown.

Please read the style guide for ROS to allow for some coherence in our project
http://wiki.ros.org/CppStyleGuide

Installation and Compilation 
=============================
Currently, the ROS distribution we are using is ROS Jade.
1. Follow ALL the instructions on: http://wiki.ros.org/jade/Installation/Ubuntu
	1. Install the desktop-full
2. Use rosdep to solve most package issues: http://wiki.ros.org/rosdep
	1. Use `rosdep install --from-paths src --ignore-src -r -y` in catkin workspace (~/catkin_ws/)
3. sudo apt-get install joystick xboxdrv
4... and couple other packages

Guidelines for compiling using catkin
---------------------
1. When removing package for catkin_make, either put CATKIN_IGNORE file in the package folder or 
2. (Preferred) put it into the donotbuild folder to make it more clear
3. Usually, cmake errors are accompanied by compile error message above the terminal ... reference that to solve the issue
4. You can build just one package using catkin_make --pkg {pkg_name} 
5. Another option is --from-pkg <package> - it builds package first then others
6. When having issues with commands like roscd and rosrun, make sure to have run source ~/catkin_ws/devel/setup.bash

Other packages that may be required 
-------------------------
* Install Eigen library 
1. Install tar.bz2 from website and follow INSTALL instruction)
2. If Cmake error, find FindEigen3.cmake file and put in it appropriate place, then rename it back to FindEigen.cmake
* (Look inside the cmake folder somewhere within the compiled library folder and paste the cmake files into the catkin folder of the package)
* Install orocos-bfl (sudo apt-get install ros-jade-navigation) 
* Install dependencies for openslam-gmapping (sudo apt-get install ros-jade-openslam-gmapping)
* Install popt.h (sudo apt-get install libpopt-dev)

Running the Robot
==================

Troubleshooting motor controller
---------------------
1. First, try resetting the motor controller (using two hardware switch)
2. Ensure that the encoder is connected
3. Verify the connection to the motor controller with an onboard switch

Running motors with Xbox controller
--------------------
1. Set up the drivers for Xbox Controller

`sudo xboxdrv --silent`

2. Run scripts that translate joystick input

`rosrun joy joy_node`
`rosrun igvc xbox_drive.py`

3. Run motor controller
    
`rosrun igvc motor_controller.py `

  1. Take note of the serial port listed in motor_controller.py 
     and make sure it is the serial port of the motor controller

The pipeline goes as follows for manual control 
joystick input (joy_node) --> motor_speed / motor_turn (xbox_drive.py) --> motor commands (motor_controller)

Current issue: The motor control via Xbox controller stops every second due to safety lock on controller - 
		 the solution would be to have a thread that sends out constant char AND update joy node to 
		 publish regardless of the command (it publishes only if the input changes).

password: Contact jinpyojeon@trincoll.edu / Jin

GPS
-----------
`rosrun nmea_navsat_driver nmea_serial_driver _port=/dev/ttyUSB0`  (or other port)

USB/Port access
---------------
1. Modify the /etc/local file. 
2. Use lsusb to list all USB devices (to test the connections)
3. ? Run python -m serial.tools.list_ports to see available ports (may be incomplete)
4. ? Run python -m serial.tools.miniterm
 
Running the robot
------------------------
launch the earl.launch file in igvc/src

Emergency Lights
-----------------
The lights will be attached to the arduino, 
with its cables attached to port 13 (signal), power 3.3v, and ground.
Its functions are handled in the multiplexer.py

Launching Phidgets (3/3/3 IMU (Inertial Measurement Unit))
----------------------
roslaunch phidgets_imu imu.launch

Setting up the Jetsons and Connecting to Camera
----------------------
######For serial - try this if ssh is not setup due to system failure
1. Refer https://demotomohiro.github.io/hardware/jetson_tk1/setup/serial.html
2. sudo screen /dev/ttyUSB0 115200
3. You can also try with the more-featured minicom program if you need more features (replace screen with minicom)
4. The USB-serial cable that we have need a 'gender changer' or adapter

######If connected via network
1. ssh -X ubuntu@Jetson1 (or Jetson IP address)
2. ssh -X ubuntu@Jetson2 

Modify the /etc/hosts to properly point the IP address of Jetsons to their name - refer to ROS on multiple networks page

3. Run *source devel/setup.bash* on each (or, better, put those commands in ~/.bashrc if not already)

4. roslaunch image_transport_package steam.launch
