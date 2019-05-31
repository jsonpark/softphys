#include "softphys/physics/physics.h"

#include "softphys/physics/object/primitive_sphere.h"

namespace softphys
{
Physics::Physics() = default;

Physics::~Physics() = default;

void Physics::SetGravity(double g)
{
  SetGravity(Eigen::Vector3d(0., 0., -g));
}

void Physics::SetGravity(const Eigen::Vector3d& g)
{
  gravity_ = g;
}

void Physics::SetEarthGravity()
{
  SetGravity(9.80665);
}

void Physics::FindContacts(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2, double time)
{
  if (object1->IsGround())
  {
    if (object2->IsGround())
      return;
    if (object2->IsRigidBody())
    {
      FindContactsGroundRigidBody(std::dynamic_pointer_cast<Ground>(object1), std::dynamic_pointer_cast<RigidBody>(object2), time);
      return;
    }
  }
  else if (object1->IsRigidBody())
  {
    if (object2->IsRigidBody())
    {
      FindContactsRigidBodies(std::dynamic_pointer_cast<RigidBody>(object1), std::dynamic_pointer_cast<RigidBody>(object2), time);
      return;
    }
  }

  // Flip
  FindContacts(object2, object1, time);
}

void Physics::FindContactsGroundRigidBody(std::shared_ptr<Ground> ground, std::shared_ptr<RigidBody> rigid_body, double time)
{
  const auto& primitives = rigid_body->GetPrimitives();
  const auto& transforms = rigid_body->GetTransforms();

  Eigen::Vector3d velocity = rigid_body->GetVelocity();

  const auto& n = ground->Normal();
  const auto& gc = ground->Center();

  for (int i = 0; i < primitives.size(); i++)
  {
    const auto& primitive = primitives[i];
    const auto& transform = transforms[i];

    // TODO: add velocity due to rotation
    Eigen::Vector3d rotation_velocity = Eigen::Vector3d::Zero();

    Eigen::Vector3d p = rigid_body->GetPosition() + transform.translation();
    Eigen::Vector3d v = velocity + rotation_velocity;

    if (primitive->IsSphere())
    {
      auto sphere = std::dynamic_pointer_cast<PrimitiveSphere>(primitive);

      auto r = sphere->Radius();

      if (n.dot(p + v * time - gc) <= r)
      {
        // Contact
        if (std::abs(n.dot(v)) <= 1e-6)
        {
          Eigen::Vector3d reflect = v - 2. * n * n.dot(v);
          rigid_body->ApplyImpulse(rigid_body->GetMass() * reflect);
        }

        // Impulse
        else if (n.dot(v) <= -1e-6)
        {
          Eigen::Vector3d reflect = v - 2.5 * n * n.dot(v);
          rigid_body->ApplyImpulse(rigid_body->GetMass() * reflect);
        }
      }
    }
  }
}

void Physics::FindContactsRigidBodies(std::shared_ptr<RigidBody> rigid_body1, std::shared_ptr<RigidBody> rigid_body2, double time)
{
}

void Physics::Simulate(double time)
{
  // TODO: collision detection and response
  for (int i = 0; i < objects_.size(); i++)
  {
    for (int j = i + 1; j < objects_.size(); j++)
    {
      FindContacts(objects_[i], objects_[j], time);
    }
  }

  // Gravity
  for (auto object : objects_)
    object->ApplyGravity(gravity_);

  // Simulation for single objects
  for (auto object : objects_)
    object->Simulate(time);

  time_ += time;
}
}
