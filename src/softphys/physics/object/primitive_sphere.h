#ifndef SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_SPHERE_H_
#define SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_SPHERE_H_

#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
class PrimitiveSphere : public PrimitiveObject
{
public:
  PrimitiveSphere() = delete;

  PrimitiveSphere(std::shared_ptr<scene::Primitive> scene_primitive, double density, double radius);

  ~PrimitiveSphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  double Volume() const override;

  auto Radius() const noexcept
  {
    return radius_;
  }

private:
  double radius_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_SPHERE_H_
