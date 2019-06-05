#include "softphys/physics/physics.h"

#include "softphys/physics/object/sphere.h"

namespace softphys
{
namespace physics
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
  const auto& n = ground->Normal();
  const auto& gc = ground->Center();

  Eigen::Vector3d p = rigid_body->GetPosition();
  Eigen::Vector3d v = rigid_body->GetVelocity();

  if (rigid_body->IsSphere())
  {
    auto sphere = std::static_pointer_cast<Sphere>(rigid_body);

    auto r = sphere->Radius();

    const double restitution = 0.8;

    if (n.dot(p - gc) <= r)
    {
      // TODO: collision found
    }
  }
}

void Physics::FindContactsRigidBodies(std::shared_ptr<RigidBody> rigid_body1, std::shared_ptr<RigidBody> rigid_body2, double time)
{
  Eigen::Vector3d p1 = rigid_body1->GetPosition();
  Eigen::Vector3d v1 = rigid_body1->GetVelocity();

  Eigen::Vector3d p2 = rigid_body2->GetPosition();
  Eigen::Vector3d v2 = rigid_body2->GetVelocity();

  if (rigid_body1->IsSphere() && rigid_body2->IsSphere())
  {
    auto sphere1 = std::static_pointer_cast<Sphere>(rigid_body1);
    auto sphere2 = std::static_pointer_cast<Sphere>(rigid_body2);

    auto r1 = sphere1->Radius();
    auto r2 = sphere2->Radius();
    auto r = r1 + r2;

    Eigen::Vector3d p = p2 - p1;
    Eigen::Vector3d v = v2 - v1;

    const double restitution = 0.8;

    if (p.squaredNorm() <= r * r)
    {
      Eigen::Vector3d n = p.normalized();

      // TODO: collision found
    }
  }
}

void Physics::Simulate(double time)
{
  if (timestep_ == 0.)
    SimulateInternal(time);

  while (time >= timestep_)
  {
    SimulateInternal(timestep_);
    time -= timestep_;
  }

  if (time >= 0.)
    SimulateInternal(time);
}

void Physics::SimulateInternal(double time)
{
  // Collision detection and response
  for (int i = 0; i < objects_.size(); i++)
  {
    for (int j = i + 1; j < objects_.size(); j++)
      FindContacts(objects_[i], objects_[j], time);
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
}
