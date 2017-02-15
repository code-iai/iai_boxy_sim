#ifndef IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H
#define IAI_BOXY_SIM_FIRE_HOSE_CONTROLLER_H

#include <ros/ros.h>
#include <controller_interface/controller.h>

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
        // TODO: implement me 
        return true;
      } 

      void starting(const ros::Time& time);

      void update(const ros::Time& /*time*/, const ros::Duration& /*period*/)
      {
        // TODO: implement me 
      }
  };
}

#endif
