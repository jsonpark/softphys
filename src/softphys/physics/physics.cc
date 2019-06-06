#include "softphys/physics/physics.h"

#include <iostream>

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

void Physics::FindContacts(int i, int j, double time)
{
  std::shared_ptr<Object> object1 = objects_[i];
  std::shared_ptr<Object> object2 = objects_[j];
  if (object1->IsGround())
  {
    if (object2->IsGround())
      return;
    if (object2->IsRigidBody())
    {
      FindContactsGroundRigidBody(i, j, time);
      return;
    }
  }
  else if (object1->IsRigidBody())
  {
    if (object2->IsRigidBody())
    {
      FindContactsRigidBodies(i, j, time);
      return;
    }
  }

  // Flip
  FindContacts(j, i, time);
}

void Physics::FindContactsGroundRigidBody(int i, int j, double time)
{
  auto ground = std::static_pointer_cast<Ground>(objects_[i]);
  auto rigid_body = std::static_pointer_cast<RigidBody>(objects_[j]);

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
      // Add a new contact constraint placeholder
      const int constraint_idx = constraints_transpose_.cols();
      constraints_transpose_.conservativeResize(Eigen::NoChange, constraint_idx + 1);
      constraints_transpose_.col(constraint_idx).setZero();
      constraints_bias_.conservativeResize(constraint_idx + 1);
      constraints_bias_(constraint_idx) = 0.;

      // Ground (object i) is always fixed
      // Add a new constraint for rigid body (object j)
      const auto& x = rigid_body->GetPosition();
      const auto& p = x - n * r;
      int idx = object_to_solver_index_[j];
      constraints_transpose_.block(6 * idx, constraint_idx, 3, 1) = n;
      constraints_transpose_.block(6 * idx + 3, constraint_idx, 3, 1) = (p - x).cross(n);
      constraints_bias_(constraint_idx) = - (p - gc).dot(n) / time;
    }
  }
}

void Physics::FindContactsRigidBodies(int i, int j, double time)
{
  auto rigid_body1 = std::static_pointer_cast<RigidBody>(objects_[i]);
  auto rigid_body2 = std::static_pointer_cast<RigidBody>(objects_[j]);

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

    Eigen::Vector3d p = p1 - p2;

    const double restitution = 0.8;

    if (p.squaredNorm() <= r * r)
    {
      Eigen::Vector3d n = p.normalized();

      // Add a new contact constraint placeholder
      const int constraint_idx = constraints_transpose_.cols();
      constraints_transpose_.conservativeResize(Eigen::NoChange, constraint_idx + 1);
      constraints_transpose_.col(constraint_idx).setZero();
      constraints_bias_.conservativeResize(constraint_idx + 1);
      constraints_bias_(constraint_idx) = 0.;

      // Add a new constraint for rigid bodies (object i and j)
      const auto& x1 = rigid_body1->GetPosition();
      const auto& p1 = x1 - n * r1;
      const auto& x2 = rigid_body2->GetPosition();
      const auto& p2 = x2 + n * r2;
      int idx1 = object_to_solver_index_[i];
      int idx2 = object_to_solver_index_[j];
      constraints_transpose_.block(6 * idx1, constraint_idx, 3, 1) = -(p2 - p1);
      constraints_transpose_.block(6 * idx1 + 3, constraint_idx, 3, 1) = -(p1 - x1).cross(p2 - p1);
      constraints_transpose_.block(6 * idx2, constraint_idx, 3, 1) = p2 - p1;
      constraints_transpose_.block(6 * idx2 + 3, constraint_idx, 3, 1) = (p2 - x2).cross(p2 - p1);
      constraints_bias_(constraint_idx) = -0.5 * (p2 - p1).squaredNorm() / time;
    }
  }
}

void Physics::UpdateSolver()
{
  // Update dimensions and indices
  object_to_solver_index_.resize(objects_.size(), -1);
  num_variables_ = 0;
  for (int i = 0; i < objects_.size(); i++)
  {
    if (!objects_[i]->IsFixed())
      object_to_solver_index_[i] = num_variables_++;
  }

  // Allocate external force vector and mass matrix
  const int dim = num_variables_ * 6;
  mass_inverse_.resize(dim, dim);
  mass_inverse_.setZero();
  external_force_.resize(dim);
  external_force_.setZero();
  constraints_transpose_.resize(dim, 0);
  constraints_bias_.resize(0);

  // Set mass matrix
  for (int i = 0; i < objects_.size(); i++)
  {
    int idx = object_to_solver_index_[i];
    if (idx != -1)
    {
      auto object = objects_[i];

      mass_inverse_.block(idx * 6, idx * 6, 3, 3) = object->MassInverse();
      mass_inverse_.block(idx * 6 + 3, idx * 6 + 3, 3, 3) = object->InertiaInverse();
    }
  }
}

void Physics::Simulate(double time)
{
  if (should_update_solver_)
  {
    UpdateSolver();
    should_update_solver_ = false;
  }

  if (timestep_ == 0.)
  {
    SimulateInternal(time);
  }
  else
  {
    while (time >= timestep_)
    {
      SimulateInternal(timestep_);
      time -= timestep_;
    }

    if (time >= 0.)
      SimulateInternal(time);
  }
}

void Physics::SimulateInternal(double time)
{
  // Reset previous constraints
  const int dim = num_variables_ * 6;
  constraints_transpose_.resize(Eigen::NoChange, 0);
  constraints_bias_.resize(0);

  // Collision detection and response
  for (int i = 0; i < objects_.size(); i++)
  {
    for (int j = i + 1; j < objects_.size(); j++)
      FindContacts(i, j, time);
  }

  // Gravity as external forces
  external_force_.setZero();
  for (int i = 0; i < objects_.size(); i++)
  {
    int idx = object_to_solver_index_[i];
    if (idx != -1)
    {
      auto object = objects_[i];
      if (object->IsRigidBody())
      {
        auto rb = std::static_pointer_cast<RigidBody>(object);

        external_force_.block(6 * idx, 0, 3, 1) = rb->GetMass() * gravity_;
        external_force_.block(6 * idx + 3, 0, 3, 1).setZero();
      }
    }
  }

  VectorXd force;
  force.resize(dim);
  force.setZero();

  if (constraints_transpose_.cols() != 0)
  {
    // If any constraint exists, solve the constrained problem
    VectorXd v;
    v.resize(dim);

    for (int i = 0; i < objects_.size(); i++)
    {
      int idx = object_to_solver_index_[i];
      if (idx != -1)
      {
        auto object = objects_[i];
        if (object->IsRigidBody())
        {
          auto rb = std::static_pointer_cast<RigidBody>(object);

          v.block(6 * idx, 0, 3, 1) = rb->GetVelocity();
          v.block(6 * idx + 3, 0, 3, 1) = rb->GetAngularVelocity();
        }
      }
    }

    MatrixXd A = constraints_transpose_.transpose() * mass_inverse_ * constraints_transpose_;
    MatrixXd b = constraints_bias_ / time - constraints_transpose_.transpose() * (v / time + mass_inverse_ * external_force_);

    // J^T M^-1 J is positive semidefinite, as so inertia/mass matrix are.
    // Eigen LDLT solver fits for the problem
    VectorXd lambda = A.ldlt().solve(b);
    VectorXd constraint_force = constraints_transpose_ * lambda;

    force = constraint_force + external_force_;
  }
  else
  {
    // Otherwise, just apply external forces
    force = external_force_;
  }

  for (int i = 0; i < objects_.size(); i++)
  {
    int idx = object_to_solver_index_[i];
    if (idx != -1)
    {
      auto object = objects_[i];

      if (object->IsRigidBody())
      {
        auto rb = std::static_pointer_cast<RigidBody>(object);
        rb->ApplyForce(force.block(6 * idx, 0, 3, 1));
        rb->ApplyTorque(force.block(6 * idx + 3, 0, 3, 1));
      }
    }
  }

  // Simulation for single objects
  for (auto object : objects_)
    object->Simulate(time);

  time_ += time;
}
}
}
