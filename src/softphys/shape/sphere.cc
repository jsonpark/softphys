#include "softphys/shape/sphere.h"

namespace softphys
{
Sphere::Sphere() = default;

Sphere::Sphere(double radius)
  : radius_(radius)
{
}

Sphere::Sphere(double radius, const Eigen::Vector3d& center)
  : radius_(radius), center_(center)
{
}

Sphere::~Sphere() = default;
}
