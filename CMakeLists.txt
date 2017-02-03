cmake_minimum_required(VERSION 2.8.3)
project(iai_boxy_sim)

find_package(catkin REQUIRED COMPONENTS
  iai_boxy_description
  ros_control_boilerplate)

catkin_package()
