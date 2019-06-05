#ifndef SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
#define SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_

#include "softphys/physics/object/object.h"

#include <vector>

#include "softphys/data/eigen.h"

namespace softphys
{
namespace physics
{
class RigidBody : public Object
{
public:
  RigidBody();
  ~RigidBody();

  bool IsRigidBody() const noexcept override
  {
    return true;
  }

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual bool IsCube() const noexcept
  {
    return false;
  }

  void SetPosition(const Eigen::Vector3d& position)
  {
    position_ = position;
  }

  void SetOrientation(const Eigen::Quaterniond& orientation)
  {
    orientation_ = orientation;
  }

  const auto& GetCom()
  {
    return com_;
  }

  auto GetMass()
  {
    return mass_;
  }

  const auto& GetPosition()
  {
    return position_;
  }

  const auto& GetOrientation()
  {
    return orientation_;
  }

  void SetMomentum(const Eigen::Vector3d& p)
  {
    momentum_ = p;
  }

  void SetVelocity(const Eigen::Vector3d& v)
  {
    momentum_ = mass_ * v;
  }

  void SetAngularMomentum(const Eigen::Vector3d& l)
  {
    angular_momentum_ = l;
  }

  virtual void ApplyImpulse(const Eigen::Vector3d& j) override;
  virtual void ApplyForce(const Eigen::Vector3d& f) override;
  virtual void ApplyGravity(const Eigen::Vector3d& g) override;
  virtual void ApplyContactConstraint(const Eigen::Vector3d& n) override;

  virtual void Simulate(double time) override;

  Eigen::Vector3d GetVelocity() const
  {
    return momentum_ / mass_;
  }

protected:
  void SetMass(double mass)
  {
    mass_ = mass;
  }

  void SetCom(const Vector3d& com)
  {
    com_ = com;
  }

  void SetInertia(const Matrix3d& inertia)
  {
    inertia_ = inertia;
  }

  void SetDiagonalInertia(const Vector3d& d)
  {
    inertia_.setZero();
    inertia_(0, 0) = d(0);
    inertia_(1, 1) = d(1);
    inertia_(2, 2) = d(2);
  }

private:
  // property
  double mass_ = 0.;
  Matrix3d inertia_{ Matrix3d::Identity() };
  Vector3d com_{ 0., 0., 0. };

  // status (linear)
  Vector3d position_{ 0., 0., 0. };
  Vector3d momentum_{ 0., 0., 0. };

  // status (rotation)
  Quaterniond orientation_{ Quaterniond::Identity() };
  Vector3d angular_momentum_{ 0., 0., 0. };

  // simulation
  Vector3d impulse_{ 0., 0., 0. };
  Vector3d force_{ 0., 0., 0. };
  std::vector<Eigen::Vector3d> contact_constraints_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
