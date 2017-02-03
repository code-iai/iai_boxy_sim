cmake_minimum_required(VERSION 2.8.3)
project(iai_boxy_sim)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  nav_msgs
  iai_boxy_description
  ros_control_boilerplate)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(odometry_simulation src/${PROJECT_NAME}/odometry_simulation.cpp)
target_link_libraries(odometry_simulation ${catkin_LIBRARIES})
