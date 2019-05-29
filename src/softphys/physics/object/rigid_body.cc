#include "softphys/physics/object/rigid_body.h"

namespace softphys
{
RigidBody::RigidBody(double mass, std::shared_ptr<Shape> shape)
  : mass_(mass), shape_(shape)
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

void RigidBody::ApplyGravity(const Eigen::Vector3d& g)
{
  force_ += g * mass_;
}

void RigidBody::Simulate(double time)
{
  // Status change due to a uniform force over time
  com_ += (momentum_ * time + 0.5 * force_ * time * time) / mass_;
  momentum_ += force_ * time;

  // After a simulation of a timestep, reset forces to 0
  force_.setZero();
}
}
