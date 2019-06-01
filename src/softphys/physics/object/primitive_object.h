#ifndef SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
#define SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_

#include <Eigen/Dense>

#include "softphys/scene/scene_primitive.h"

namespace softphys
{
class PrimitiveObject
{
public:
  PrimitiveObject() = delete;

  PrimitiveObject(std::shared_ptr<scene::Primitive> scene_primitive, double density);

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

  auto ScenePrimitive() const
  {
    return scene_primitive_;
  }

private:
  std::shared_ptr<scene::Primitive> scene_primitive_;
  double density_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_OBJECT_H_
