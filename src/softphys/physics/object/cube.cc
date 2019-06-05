#include "softphys/physics/object/cube.h"

namespace softphys
{
namespace physics
{
Cube::Cube(const Vector3d& size, double density)
  : RigidBody(),
  density_(density), size_(size)
{
  SetMass(density * Volume());

  double coeff = 1. / 12. * GetMass();
  SetDiagonalInertia(coeff * Vector3d(size(1) * size(1) + size(2) * size(2), size(0) * size(0) + size(2) * size(2), size(0) * size(0) + size(1) * size(1)));
}

Cube::~Cube() = default;

double Cube::Volume() const
{
  return 8. * size_(0) * size_(1) * size_(2);
}
}
}
