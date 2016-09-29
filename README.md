#test_tm_driver
tm_driver test without using ROS

## Installation
1. create a folder ```test_rm_dreiver``` for this test code
2. copy the *CMakeLists.txt* and *test_tm_driver.cpp* to ```test_rm_dreiver/```
3. copy the ```src``` folder in ```techman_robot/tm_driver/``` to ```test_rm_dreiver/```
4. copy the ```tm_driver``` folder in ```techman_robot/tm_driver/include/``` to ```test_rm_dreiver/```
5. ```$ cmake .``` and ```$ make``` to build this test code

## Usage
To start this test program:
```
$ ./test_tm_driver 192.168.0.10
```
during the execution
* input ```start``` to connect to techman robot
* input ```halt``` to disconnect to techman robot
* input ```quit``` to exit the program

if the connection is success
* input ```datart``` to print all robot_state_rt once
* input ```show``` to print robot_state cyclic, type ```1, 2, ..., 9, 0``` to change data type, type ```q``` to leave the loop
* there are other commands: ```clear```, ```movjabs```, etc

TODO: the usage of all robot commands...
