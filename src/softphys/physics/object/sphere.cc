#include "softphys/physics/object/sphere.h"

namespace softphys
{
namespace physics
{
Sphere::Sphere(double radius, double density)
  : RigidBody(),
  density_(density), radius_(radius)
{
  SetMass(density * Volume());
}

Sphere::Sphere(const std::string& model_name, double radius, double density)
  : RigidBody(model_name),
  density_(density), radius_(radius)
{
  SetMass(density * Volume());
}

Sphere::~Sphere() = default;

double Sphere::Volume() const
{
  return 4. / 3. * std::acos(-1.) * radius_ * radius_ * radius_;
}
}
}
