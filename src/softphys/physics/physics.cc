#include "softphys/physics/physics.h"

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

void Physics::Simulate(double time)
{
  // TODO: collision detection and response
  for (int i = 0; i < objects_.size(); i++)
  {
    for (int j = i + 1; j < objects_.size(); j++)
    {
    }
  }

  // Gravity
  for (auto object : objects_)
    object->ApplyForce(gravity_);

  // Simulation for single objects
  for (auto object : objects_)
    object->Simulate(time);

  time_ += time;
}
}
