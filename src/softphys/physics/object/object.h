#ifndef SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_

#include <Eigen/Dense>

namespace softphys
{
class Object
{
public:
  Object();
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

  virtual void Simulate(double time);

private:
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
