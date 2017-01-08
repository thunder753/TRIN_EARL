#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>

// cstring is probably safer choice for serial data
#include <cstring>
// For serial communication
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
// C++ library for ports and hex handling
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <boost/lexical_cast>
#include <iomanip>
#include <sstream>
// For info on serial comm for Roboteq AX3500, see pg. 138 in the manual (In drive or Google it)
// Contains node that publishes encoder node, as well as motor controlling node 

// Device port is set to be accessed globally
boost::asio::io_service io;
boost::asio::serial_port port(io);

using namespace std;

string COM_FOR_CH1 = "!A"; // Add two string nn for speed in Hex, with 7F being max
string COM_BAC_CH1 = "!a";
string COM_FOR_CH2 = "!B"; // As above
string COM_BAC_CH2 = "!b";
string QUE_SPEED = "?K";
string QUE_BAT = "?E";
string QUE_VOLT = "?V";
const int LEFT = 0;
const int RIGHT = 1;
const int wheel_diameter = 0.42; 
const int wheel_circum = M_PI * wheel_diameter; 
const int wheel_separation = 0.69 
const float max_rpm = 3000.0 / 26.0; // wheel_rpm = motor_rpm / gear_ratio
			       //Refer https://mycontraption.com/calculating-robot-speed-and-motor-torque/
const int max_effort = 127; // 7F in int; 00-7F is the range of effort for motor message

//  Max speed comes to be about 5.63 mph ... TODO: Check on motor_rpm 

//! The node handle we'll be using
ros::NodeHandle n;

// Refer to pg. 160 for specs
// 0 is the left, 1 is right 
double get_speed(int wheel_side) {
	send_message(QUE_SPEED, strlen(QUE_SPEED)); // QUE_SPEED is cstring 
	
	try {
		int effort = lexical_cast<int>(read_port(nn));
	} catch(bad_lexical_cast&) {
		ROS_ERROR("Bad hex handling!");
	}

	float speed = wheel_circum * max_rpm * (effort * 1.0 / max_effort);

	return speed;
}

// The direction is accounted by the sign of speed
// Will need to figure out the corresponding speed for the 
void change_speed(int wheel_side, double speed) {
	// TODO: Find equation to change speed -> wheel effort
	// INFO: 26:1, effort: 00-7F, forward or backward

	int needed_effort = (int) ((speed * max_effort) / (wheel_circum * max_rpm))

	// Changing int to hex 
	// Accomodate for negative int (reverse direction ...)
	if (needed_effort < 0) {
		ROS_ERROR("Got negative speed");
		send_message(COM)
	} else if (needed_effort > 127) {
		needed_effort = 127
	}
	else {
		std::stringstream stream;
		stream << std::hex << needed_effort;
		char * 
	}

}

void send_message(char * msg, int msg_size) {
	port.write_some(boost::asio::buffer(msg, size));
}

// Called whenever the mux_cmdvel is received
void velCallback(const geometry_msgs::Twist::ConstPtr&cmd_vel) {
	// TODO: Put asserts for min and max speed if roslaunch does not properly handle

	double linear_vel = cmd_vel->linear.x;
	double angular_vel = cmd_vel->angular.x;	

	// TODO: Compensation if there is signficant motor speed differences
	
	double left_speed = linear_vel + angular_vel * wheel_separation / 2.0;
	double right_speed = linear_vel - angular_vel * wheel_separation / 2.0;

	change_speed(LEFT, left_speed);
	change_speed(RIGHT, right_speed);
}

int main(int argc, char** argv)
{
	string port_name; 
	
	//init the ROS node
	ros::init(argc, argv, "motor_controller");
	ros::NodeHandle n;
	
	if (!n.getParam("port", port_name)) 
	{
		ROS_ERROR("Failed to get param port");
		exit(-1);
	}	
	
	// Checks if we can open the port, else return error
	try {
		port.open(port_name.c_str());
	}
	catch { 
		ROS_ERROR("Could not open port");
		exit(-1);
	}

	// Refer to this link: http://www.cmrr.umn.edu/~strupp/serial.html#2_5_3
	// as well as the manual
	// The port info is baud rate 9600, 7 bit data, 1 start bit, 1 stop bit, even parity
	// Setting up port options
	port.set_option(boost::asio::serial_port_base::baud_rate(9600));
	port.set_option(boost::asio::serial_port_base::parity(
				boost::asio::serial_port_base::parity::type even));
	port.set_option(boost::asio::serial_port_base::stop_bits(
				boost::asio::serial_port_base::stop_bits::type one));

	//ros::Publisher encoder_pub = n.advertise<nav_msgs::Odometry>("motor_odom", 1000);
	
	// Odom and Transforms are handled at diff_ty.py
	ros::Publisher left_whl_pub = n.advertise<std_msgs::Float32>("lwheel", 1000);
	ros::Publisher right_whl_pub = n.advertise<std_msg::Float32>("rwheel", 1000);
	
	ros::Subscriber cmd_vel_sub = n.subscribe("mux_cmdvel", 1000, velCallback);

	ros::Rate loop_rate(10);

	ros::Time current_time = ros::Time::now();
	ros::Time last_time = ros::Time::now();
	
	std_msgs::Float32 left_wheel_speed, right_wheel_speed;	
	while (ros::ok()) {
		current_time = ros::Time::now();
		
		left_wheel_speed = get_speed(LEFT);
		right_wheel_speed = get_speed(RIGHT);	
		
		left_whl_pub.publish(left_wheel_speed);
		right_whl_pub.publish(right_wheel_speed);

		ros::spinOnce();
		loop_rate.sleep();
	}

	port.close();

	return 0;
}
