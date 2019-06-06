#ifndef SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_

#include "softphys/data/eigen.h"

namespace softphys
{
namespace physics
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

  virtual bool IsFixed() const noexcept
  {
    return true;
  }

  virtual Matrix3d MassInverse() const noexcept
  {
    return Matrix3d::Zero();
  }

  virtual Matrix3d InertiaInverse() const noexcept
  {
    return Matrix3d::Zero();
  }

  virtual void Simulate(double time);

private:
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_OBJECT_H_
