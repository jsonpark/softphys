#ifndef SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_

#include <Eigen/Dense>

#include "softphys/model/primitive/primitive.h"

namespace softphys
{
class PrimitiveObject
{
public:
  PrimitiveObject() = delete;

  PrimitiveObject(double density);
  PrimitiveObject(std::shared_ptr<model::Primitive> primitive, double density);

  virtual ~PrimitiveObject();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual double Volume() const
  {
    return 0.;
  }

  virtual Eigen::Vector3d CenterOfMass()
  {
    return Eigen::Vector3d::Zero();
  }

  double Mass() const
  {
    return Volume() * density_;
  }

  auto ModelPrimitive() const
  {
    return model_primitive_;
  }

private:
  std::shared_ptr<model::Primitive> model_primitive_;
  double density_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
