#ifndef IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H
#define IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H

#include <ros/ros.h>
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

namespace iai_boxy_sim
{
  template <class T>
  class FireHoseController: public controller_interface::Controller<T>
  {
    public:
      FireHoseController() {}
      ~FireHoseController()
      {
        // TODO: implement me 
        // sub_command_.shutdown();
      }

      bool init(T* hw, ros::NodeHandle &nh)
      {
        std::string param_name = "joints";
        if(!nh.getParam(param_name, joint_names_))
        {
          ROS_ERROR_STREAM("Failed to getParam '" << param_name << "' (namespace: " << nh.getNamespace() << ").");
          return false;
        }

        if(joint_names_.size() == 0)
        {
          ROS_ERROR_STREAM("List of joint names is empty.");
          return false;
        }

        for(size_t i=0; i<joint_names_.size(); i++)
        {
          try
          {
            joints_.push_back(hw->getHandle(joint_names_[i]));  
          }
          catch (const hardware_interface::HardwareInterfaceException& e)
          {
            ROS_ERROR_STREAM("Exception thrown: " << e.what());
            return false;
          }
        }
        // TODO: implement me 
        return true;
      } 

      void starting(const ros::Time& time);

      void update(const ros::Time& /*time*/, const ros::Duration& /*period*/)
      {
        // TODO: implement me 
      }

      std::vector<std::string> joint_names_;
      std::vector< hardware_interface::JointHandle > joints_;
  };
}

#endif
