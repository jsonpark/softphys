#include "softphys/scene/scene_sphere.h"

namespace softphys
{
namespace scene
{
Sphere::Sphere(double density, int material, double radius)
  : Primitive(density, material),
  radius_(radius)
{
}

Sphere::~Sphere() = default;
}
}
