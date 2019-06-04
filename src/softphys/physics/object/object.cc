#include "softphys/physics/object/object.h"

namespace softphys
{
namespace physics
{
Object::Object() = default;

Object::Object(const std::string& model_name)
  : model_name_(model_name)
{
}

Object::~Object() = default;

void Object::ApplyImpulse(const Eigen::Vector3d& j)
{
}

void Object::ApplyForce(const Eigen::Vector3d& f)
{
}

void Object::ApplyGravity(const Eigen::Vector3d& g)
{
}

void Object::ApplyContactConstraint(const Eigen::Vector3d& n)
{
}

void Object::Simulate(double time)
{
}
}
}
