#include "softphys/object/sphere.h"

namespace softphys
{
Sphere::Sphere() = default;

Sphere::Sphere(double radius)
  : radius_(radius)
{
}

Sphere::~Sphere() = default;
}
