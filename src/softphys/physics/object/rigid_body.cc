#include "softphys/physics/object/rigid_body.h"

#include <iostream>

namespace softphys
{
namespace physics
{
RigidBody::RigidBody() = default;

RigidBody::~RigidBody() = default;

void RigidBody::ApplyImpulse(const Eigen::Vector3d& j)
{
  impulse_ += j;
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
  momentum_ += force_ * time;
  position_ += momentum_ * time / mass_;

  // Status change - orientation
  // angular_monmentum_ += torque_ * time;
  Vector3d v = 0.5 * inertia_.inverse() * angular_momentum_;
  Quaterniond q = Quaterniond(0., v(0), v(1), v(2)) * orientation_;
  orientation_.w() += q.w() * time;
  orientation_.x() += q.x() * time;
  orientation_.y() += q.y() * time;
  orientation_.z() += q.z() * time;
  orientation_.normalize();

  // After a simulation of a timestep, reset forces to 0
  impulse_.setZero();
  force_.setZero();
}
}
}
