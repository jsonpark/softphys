#include "softphys/physics/object/rigid_body.h"

#include <iostream>

namespace softphys
{
RigidBody::RigidBody() = default;

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
  position_ += (momentum_ * time + 0.5 * force_ * time * time) / mass_;
  momentum_ += force_ * time;

  // After a simulation of a timestep, reset forces to 0
  force_.setZero();
}
}
