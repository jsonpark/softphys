#include "softphys/physics/object/simulation_ground.h"

namespace softphys
{
SimulationGround::SimulationGround(const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : normal_(normal), center_(center)
{
}

SimulationGround::~SimulationGround() = default;
}
