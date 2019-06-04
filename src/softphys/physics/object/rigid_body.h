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
  RigidBody(const std::string& model_name);
  ~RigidBody();

  bool IsRigidBody() const noexcept override
  {
    return true;
  }

  virtual bool IsSphere() const noexcept
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

private:
  // property
  double mass_ = 0.;
  Vector3d com_{ 0., 0., 0. };

  // status (linear)
  Vector3d position_{ 0., 0., 0. };
  Vector3d momentum_{ 0., 0., 0. };

  // status (rotation)
  Quaterniond orientation_{ Quaterniond::Identity() };

  // simulation
  Vector3d impulse_{ 0., 0., 0. };
  Vector3d force_{ 0., 0., 0. };
  std::vector<Eigen::Vector3d> contact_constraints_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
