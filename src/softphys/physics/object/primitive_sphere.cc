#include "softphys/physics/object/primitive_sphere.h"

namespace softphys
{
PrimitiveSphere::PrimitiveSphere(double density, double radius)
  : PrimitiveObject(density),
  radius_(radius)
{
}

PrimitiveSphere::~PrimitiveSphere() = default;

double PrimitiveSphere::Volume()
{
  return 4. / 3. * std::acos(-1.) * radius_ * radius_ * radius_;
}
}
