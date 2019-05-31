#ifndef SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_

#include <Eigen/Dense>

#include "softphys/shape/shape.h"

namespace softphys
{
class PrimitiveObject
{
public:
  PrimitiveObject() = delete;

  PrimitiveObject(double density);

  virtual ~PrimitiveObject();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual double Volume()
  {
    return 0.;
  }

  virtual Eigen::Vector3d CenterOfMass()
  {
    return Eigen::Vector3d::Zero();
  }

  double Mass()
  {
    return Volume() * density_;
  }

private:
  double density_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
