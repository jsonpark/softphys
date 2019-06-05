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
  SetDiagonalInertia(2. / 5. * GetMass() * radius_ * radius_ * Vector3d(1., 1., 1.));
}

Sphere::~Sphere() = default;

double Sphere::Volume() const
{
  return 4. / 3. * std::acos(-1.) * radius_ * radius_ * radius_;
}
}
}
