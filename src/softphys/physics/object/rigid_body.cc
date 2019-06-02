#include "softphys/physics/object/rigid_body.h"

#include <iostream>

namespace softphys
{
RigidBody::RigidBody(std::shared_ptr<scene::Object> scene_object)
  : SimulationObject(scene_object)
{
}

RigidBody::~RigidBody() = default;

void RigidBody::AttachPrimitive(std::shared_ptr<PrimitiveObject> primitive, const Eigen::Affine3d& transform)
{
  primitives_.push_back(primitive);
  transforms_.push_back(transform);

  auto p_com = transform * primitive->CenterOfMass();
  auto p_mass = primitive->Mass();

  // Center of mass update
  if (mass_ + p_mass > 1e-6)
    com_ = (com_ * mass_ + p_com * p_mass) / (mass_ + p_mass);
  mass_ += p_mass;
}

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

  // After a simulation of a timestep, reset forces to 0
  impulse_.setZero();
  force_.setZero();
  contact_constraints_.clear();
}
}
