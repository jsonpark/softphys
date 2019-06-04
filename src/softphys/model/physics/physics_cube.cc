#include "softphys/model/physics/physics_cube.h"

namespace softphys
{
namespace model
{
PhysicsCube::PhysicsCube(const Vector3d& size, double density)
  : Physics(),
  size_(size), density_(density)
{
}

PhysicsCube::~PhysicsCube() = default;
}
}
