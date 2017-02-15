cmake_minimum_required(VERSION 2.8.3)
project(iai_boxy_sim)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  nav_msgs
  giskard_msgs
  iai_boxy_description
  ros_control_boilerplate
  controller_interface
  hardware_interface
  realtime_tools
  pluginlib
  )

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/velocity_fire_hose_controller.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

add_executable(odometry_simulation src/${PROJECT_NAME}/odometry_simulation.cpp)
target_link_libraries(odometry_simulation ${catkin_LIBRARIES})
