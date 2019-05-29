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

  virtual void ApplyImpulse(const Eigen::Vector3d& impulse);
  virtual void ApplyForce(const Eigen::Vector3d& f);
  virtual void Simulate(double time);

private:
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
