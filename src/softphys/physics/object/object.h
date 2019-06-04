#ifndef SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_

#include <Eigen/Dense>

namespace softphys
{
namespace physics
{
class Object
{
public:
  Object();
  Object(const std::string& model_name);
  virtual ~Object();

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

  const auto& ModelName() const
  {
    return model_name_;
  }

private:
  std::string model_name_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
