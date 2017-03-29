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

## Usage
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

### Move the base
You can try the odometry simulation by sending commands from the shell:
```
rostopic pub /odom_sim/command geometry_msgs/Twist "linear:                                                        
  x: 0.1
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.1" -r 20
```
This should translate and rotate the robot. The odometry simulation has a watchdog inside. So, just kill the publisher in the shell, and the robot should stop moving.
