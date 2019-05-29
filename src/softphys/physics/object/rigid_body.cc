#include "softphys/physics/object/rigid_body.h"

namespace softphys
{
RigidBody::RigidBody(double mass)
  : mass_(mass)
{
}

RigidBody::~RigidBody() = default;

void RigidBody::ApplyImpulse(const Eigen::Vector3d& j)
{
  momentum_ += j;
}

void RigidBody::ApplyForce(const Eigen::Vector3d& f)
{
  force_ += f;
}

void RigidBody::Simulate(double time)
{
  // Status change due to a uniform force over time
  com_ += momentum_ * time + 0.5 * force_ * time * time;
  momentum_ += force_ * time;

  // After a simulation of a timestep, reset forces to 0
  force_.setZero();
}
}
