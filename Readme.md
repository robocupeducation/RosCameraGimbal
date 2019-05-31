# How does the module work

## Step 1: Install arduino rosserial

In order to make working this module you must install in your ROS station arduino roserial, so please visit the following link : http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

## Step 2: Load this software on arduino board

Clone this repository and then load ServoSub.ino on your arduino board. Notice that you should have arduino rosserial in your arduino IDE in order to
compile the program in the IDE.

## Step 3: Setting up the enviroment

When software was loaded in your board is the moment to run the following commands in your ros enviroment (notice that you'll have to open several
command prompts)

+ roscore

+ rosrun rosserial_python serial_node.py /dev/ttyUSBx   (where USBx is the serial port where your arduino is attached)

+ rostopic pub /Servocontrol std_msgs/UInt8MultiArray '{data: [0,180]}' (Where the first field identifies servo and the second the position where it should move)
