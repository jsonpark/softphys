#ifndef SOFTPHYS_PHYSICS_OBJECT_SIMULATION_GROUND_H_
#define SOFTPHYS_PHYSICS_OBJECT_SIMULATION_GROUND_H_

#include "softphys/physics/object/simulation_object.h"

namespace softphys
{
class SimulationGround : public SimulationObject
{
public:
  SimulationGround() = delete;
  SimulationGround(std::shared_ptr<scene::Object> scene_object, const Eigen::Vector3d& normal, const Eigen::Vector3d& center);
  ~SimulationGround();

  bool IsGround() const noexcept override
  {
    return true;
  }

  const auto& Normal() const noexcept
  {
    return normal_;
  }

  const auto& Center() const noexcept
  {
    return center_;
  }

private:
  Eigen::Vector3d normal_;
  Eigen::Vector3d center_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_SIMULATION_GROUND_H_
