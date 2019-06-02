#ifndef SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_

#include <Eigen/Dense>

namespace softphys
{
class SimulationObject
{
public:
  SimulationObject() = delete;
  SimulationObject(const std::string& model_name);
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
  virtual void ApplyContactConstraint(const Eigen::Vector3d& n);

  virtual void Simulate(double time);

  auto ModelName() const
  {
    return model_name_;
  }

private:
  const std::string& model_name_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_SIMULATION_OBJECT_H_
