#include "softphys/physics/object/simulation_ground.h"

namespace softphys
{
SimulationGround::SimulationGround(const std::string& model_name, const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : SimulationObject(model_name),
  normal_(normal), center_(center)
{
}

SimulationGround::~SimulationGround() = default;
}
