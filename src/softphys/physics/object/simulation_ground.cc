#include "softphys/physics/object/simulation_ground.h"

namespace softphys
{
SimulationGround::SimulationGround(std::shared_ptr<scene::Object> scene_object, const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : SimulationObject(scene_object),
  normal_(normal), center_(center)
{
}

SimulationGround::~SimulationGround() = default;
}
