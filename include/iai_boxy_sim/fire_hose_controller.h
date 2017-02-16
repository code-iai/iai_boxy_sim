#ifndef IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H
#define IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H

#include <ros/ros.h>
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <giskard_msgs/SemanticFloat64Array.h>
#include <realtime_tools/realtime_buffer.h>

namespace iai_boxy_sim
{
  template <class T>
  class FireHoseController: public controller_interface::Controller<T>
  {
    public:
      FireHoseController() {}
      ~FireHoseController()
      {
        subscriber_.shutdown();
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

        commands_buffer_.writeFromNonRT(std::vector<double>(joint_names_.size(), 0.0));

        subscriber_ = nh.subscribe<giskard_msgs::SemanticFloat64Array>("command", 1, 
            &FireHoseController::callback, this);
        return true;
      } 

      void starting(const ros::Time& time);

      void update(const ros::Time& time, const ros::Duration& period)
      {
        std::vector<double> & commands = *commands_buffer_.readFromRT();
        for(unsigned int i=0; i<joint_names_.size(); ++i)
          joints_[i].setCommand(commands[i]);
      }

    protected:
      std::vector<std::string> joint_names_;
      std::vector< hardware_interface::JointHandle > joints_;
      realtime_tools::RealtimeBuffer<std::vector<double> > commands_buffer_;

    private:
      ros::Subscriber subscriber_;

      void callback(const giskard_msgs::SemanticFloat64ArrayConstPtr& msg) 
      {
        std::map<std::string, double> index;
        for (size_t i=0; i<msg->data.size(); ++i)
          index.insert(std::pair<std::string, double>(msg->data[i].semantics, msg->data[i].value));

        std::vector<double> new_cmd = *(commands_buffer_.readFromNonRT());
        for (size_t i=0; i<joint_names_.size(); ++i)
        {
          typename std::map<std::string, double>::const_iterator it = index.find(joint_names_[i]);
          if( it != index.end())
          {
            new_cmd[i] = it->second;
          }
           // TODO: implement else branch with watchdog functionality
        }
        
        commands_buffer_.writeFromNonRT(new_cmd);

//                  if(msg->data.size()!=n_joints_)
//                        { 
//                                ROS_ERROR_STREAM("Dimension of command (" << msg->data.size() << ") does not match number of joints (" << n_joints_ << ")! Not executing!");
//                                      return; 
//                                          }
//                      commands_buffer_.writeFromNonRT(msg->data);
       }
  };
}

#endif
