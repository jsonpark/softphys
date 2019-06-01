#ifndef SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_

#include <Eigen/Dense>

#include "softphys/scene/scene_object.h"

namespace softphys
{
class SimulationObject
{
public:
  SimulationObject() = delete;
  SimulationObject(std::shared_ptr<scene::Object> scene_object);
  virtual ~SimulationObject();

  virtual bool IsRigidBody() const noexcept
  {
    return false;
  }

  virtual bool IsGround() const noexcept
  {
    return false;
  }

  virtual void ApplyImpulse(const Eigen::Vector3d& j);
  virtual void ApplyForce(const Eigen::Vector3d& f);
  virtual void ApplyGravity(const Eigen::Vector3d& g);

  virtual void Simulate(double time);

  auto SceneObject() const
  {
    return scene_object_;
  }

private:
  std::shared_ptr<scene::Object> scene_object_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_
