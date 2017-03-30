# iai_boxy_sim
A lightweight kinematics simulation of IAI's Boxy robot.

## Installation
Using ```catkin_tools``` and ```wstool``` in a new workspace for ```ROS Indigo``` installed on ```Ubuntu 14.04```:
```
source /opt/ros/indigo/setup.bash          # start using ROS Indigo
mkdir -p ~/my_ws/src                       # create directory for workspace
cd ~/my_ws                                 # go to workspace directory
catkin init                                # init workspace
cd src                                     # go to source directory of workspace
wstool init                                # init rosinstall
wstool merge https://raw.githubusercontent.com/code-iai/iai_boxy_sim/master/rosinstall/catkin.rosinstall
                                           # update rosinstall file
wstool update                              # pull source repositories
rosdep install --ignore-src --from-paths . # install dependencies available through apt
catkin build                               # build packages
source ~/my_ws/devel/setup.bash            # source new overlay
```
Note, the above instructions have been tested to also work under ```ROS Kinetic``` installed on ```Ubuntu 16.04```. Just replace any occurance of ```indigo``` with ```kinetic```.

## Design decisions
There were some major design decisions that went into this simulator. Some of them diverge from typical ROS standards:
* Model the odometry as 3 robots joints in the URDF. As a result, the odometry joints get published over the ```/joint_states``` topic, and the corresponding TF frames get published by the ```robot_state_publisher```. Rational: This treats base joints just like arm joints. KISS principle.
* Have only one command topic for the entire robot (including odometry). The simulator (and the actual robot) will take care of delegating the respective sub-commands to the correct body parts or joints. As Alexis calls it: "Drinking from the fire hose." Rational: This ensures that whole-body command are sent together and arrive at the low-level controllers at the same time with the same time stamps.
* Use ```sensor_msgs/JointState``` as message type for the command topic. Rational: Use readily available message definitions instead of defining custom messages. Again, KISS principle.
* Allow sending of commands for only parts of the body. Rational: This speeds up conducting experiments with only parts of the robot.

## Tutorials
### Visualize simulated robot in RVIZ

![rviz view](https://raw.githubusercontent.com/code-iai/iai_boxy_sim/master/docs/boxy_sim_rviz.png)

In a first shell, run:
```
roslaunch iai_boxy_sim boxy.launch     # start simulation
```
In a second shell, enter:
```
rviz                                       # start rviz
```
In rviz, add a plugin of type ```RobotModel```, and select as ```Fixed_Frame``` the frame ```map```.

### Moving the robot through the command topic
There are two test bash-scripts that move parts of the robots. The scripts just publish command messages over the ```~command``` topic that the simulator subscribes to.


Moving the arms:
```shell
rosrun iai_boxy_sim move_arms
```

Which does this:
```shell
rostopic pub /boxy/commands sensor_msgs/JointState "header:
  seq: 0
  stamp: {secs: 0, nsecs: 0}
  frame_id: ''
name: ['right_arm_4_joint', 'left_arm_0_joint', 'left_arm_1_joint']
position: [0, 0, 0]
velocity: [-0.1, -0.1, -0.1]
effort: [0]" -r 100
```

Moving the base:
```shell
rosrun iai_boxy_sim move_base
```

Which does this:
```shell
rostopic pub /boxy/commands sensor_msgs/JointState "header:
  seq: 0
  stamp: {secs: 0, nsecs: 0}
  frame_id: ''
name: ['odom_x_joint', 'odom_z_joint']
position: [0, 0]
velocity: [0.2, 0.1]
effort: [0]" -r 100
```
As you can see, the simulator correctly moves the command joints using the name fields.

Note: Even if you only want to send velocity commands, it is necessary to fill the position field with the appropriate amount of numbers. The efforts field is ignored.

## ROS Interface
![rviz view](https://raw.githubusercontent.com/code-iai/iai_boxy_sim/master/docs/boxy_sim.svg.png)

### Subscribed topics
* ```~commands``` (sensor_msgs/JointState): instantaneous motion commands to joints; currently only ```velocity``` field is used; fields ```name```, ```position```, ```velocity``` need to have lists of equal length; partial commands are supported

### Published topics
* ```~joint_states``` (sensor_msgs/JointState): complete joint state of the simulated robot

### Offered Services
* ```~set_joint_states``` (iai_naive_kinematics_sim/SetJointState): set next joint of the simulated robot; partial commands are supported

### Parameters

to be done.

## Known limitations
* Position commands are not support, yet. There are plans to support this.
* Efforts are not simulated. This will not be supported in the future.
