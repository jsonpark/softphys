#include "softphys/physics/object/rigid_body.h"

#include <iostream>

namespace softphys
{
namespace physics
{
RigidBody::RigidBody() = default;

RigidBody::RigidBody(const std::string& model_name)
  : Object(model_name)
{
}

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

void RigidBody::ApplyContactConstraint(const Eigen::Vector3d& n)
{
  contact_constraints_.push_back(n);
}

void RigidBody::Simulate(double time)
{
  for (const auto& n : contact_constraints_)
  {
    if (n.dot(impulse_) <= 0.)
      impulse_ -= n.dot(impulse_) * n;
    if (n.dot(force_) <= 0.)
      force_ -= n.dot(force_) * n;
  }

  // Status change due to a uniform force over time
  momentum_ += impulse_ + force_ * time;
  position_ += momentum_ * time / mass_;

  for (const auto& n : contact_constraints_)
  {
    if (n.dot(momentum_) <= 0.)
      momentum_ -= n.dot(momentum_) * n;
  }

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
  contact_constraints_.clear();
}
}
}
