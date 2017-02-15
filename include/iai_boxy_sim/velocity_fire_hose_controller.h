#ifndef IAI_BOXY_SIM_VELOCITY_FIRE_HOSE_CONTROLLER_H
#define IAI_BOXY_SIM_VELOCITY_FIRE_HOSE_CONTROLLER_H

#include <iai_boxy_sim/fire_hose_controller.h>
#include <hardware_interface/joint_command_interface.h>

namespace iai_boxy_sim
{
  typedef FireHoseController<hardware_interface::VelocityJointInterface>
    VelocityFireHoseController;
}

#endif
