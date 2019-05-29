#include "softphys/physics/object/object.h"

namespace softphys
{
Object::Object() = default;

Object::~Object() = default;

void Object::ApplyImpulse(const Eigen::Vector3d& impulse)
{
}

void Object::ApplyForce(const Eigen::Vector3d& f)
{
}

void Object::Simulate(double time)
{
}
}
