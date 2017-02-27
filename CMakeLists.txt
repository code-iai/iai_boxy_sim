cmake_minimum_required(VERSION 2.8.3)
project(iai_boxy_sim)

find_package(catkin REQUIRED COMPONENTS
  iai_boxy_description
  iai_naive_kinematics_sim
  robot_state_publisher
  tf2_ros)

catkin_package()
