#include "softphys/physics/object/primitive_cylinder.h"

namespace softphys
{
PrimitiveCylinder::PrimitiveCylinder(std::shared_ptr<scene::Primitive> scene_primitive, double density, double radius, double height)
  : PrimitiveObject(scene_primitive, density),
  radius_(radius), height_(height)
{
}

PrimitiveCylinder::~PrimitiveCylinder() = default;

double PrimitiveCylinder::Volume() const
{
  return std::acos(-1.) * radius_ * radius_ * height_;
}
}
