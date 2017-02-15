#include <iai_boxy_sim/velocity_fire_hose_controller.h>
#include <pluginlib/class_list_macros.h>

template <class T>
void iai_boxy_sim::FireHoseController<T>::starting(const ros::Time& time)
{
  // TODO: implement me
  // Start controller with 0.0 velocities
  //   commands_buffer_.readFromRT()->assign(n_joints_, 0.0);
}
    
PLUGINLIB_EXPORT_CLASS(iai_boxy_sim::VelocityFireHoseController,controller_interface::ControllerBase)
