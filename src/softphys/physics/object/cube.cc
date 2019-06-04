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
}

Cube::Cube(const std::string& model_name, const Vector3d& size, double density)
  : RigidBody(model_name),
  density_(density), size_(size)
{
  SetMass(density * Volume());
}

Cube::~Cube() = default;

double Cube::Volume() const
{
  return 8. * size_(0) * size_(1) * size_(2);
}
}
}
