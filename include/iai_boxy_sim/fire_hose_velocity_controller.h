#ifndef IAI_BOXY_SIM_FIRE_HOSE_VELOCITY_CONTROLLER_H
#define IAI_BOXY_SIM_FIRE_HOSE_VELOCITY_CONTROLLER_H

#include <iai_boxy_sim/fire_hose_controller.h>

namespace iai_boxy_sim
{
  typedef FireHoseController<hardware_interface::VelocityJointInterface>
    FireHoseVelocityController;
}

#endif
