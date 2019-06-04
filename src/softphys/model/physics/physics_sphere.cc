#include "softphys/model/physics/physics_sphere.h"

namespace softphys
{
namespace model
{
PhysicsSphere::PhysicsSphere(double radius, double density)
  : Physics(),
  radius_(radius), density_(density)
{
}

PhysicsSphere::~PhysicsSphere() = default;
}
}
