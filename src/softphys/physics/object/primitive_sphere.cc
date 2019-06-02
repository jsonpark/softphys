#include "softphys/physics/object/primitive_sphere.h"

namespace softphys
{
PrimitiveSphere::PrimitiveSphere(double density, double radius)
  : PrimitiveObject(density),
  radius_(radius)
{
}

PrimitiveSphere::PrimitiveSphere(std::shared_ptr<model::Primitive> primitive, double density, double radius)
  : PrimitiveObject(primitive, density),
  radius_(radius)
{
}

PrimitiveSphere::~PrimitiveSphere() = default;

double PrimitiveSphere::Volume() const
{
  return 4. / 3. * std::acos(-1.) * radius_ * radius_ * radius_;
}
}
