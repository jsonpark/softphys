#ifndef SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
#define SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_

#include "softphys/physics/object/object.h"
#include "softphys/shape/shape.h"

namespace softphys
{
class RigidBody : public Object
{
public:
  RigidBody() = delete;
  RigidBody(double mass, std::shared_ptr<Shape> shape);
  ~RigidBody();

  bool IsRigidBody() const noexcept override
  {
    return true;
  }

  const auto& GetCom()
  {
    return com_;
  }

  const auto& GetRotation()
  {
    return rotation_;
  }

  void SetCom(const Eigen::Vector3d& com)
  {
    com_ = com;
  }

  void SetMomentum(const Eigen::Vector3d& p)
  {
    momentum_ = p;
  }

  void SetVelocity(const Eigen::Vector3d& v)
  {
    momentum_ = mass_ * v;
  }

  void ApplyImpulse(const Eigen::Vector3d& j) override;
  void ApplyForce(const Eigen::Vector3d& f) override;
  void ApplyGravity(const Eigen::Vector3d& g) override;
  void Simulate(double time) override;

  auto GetShape() const noexcept
  {
    return shape_;
  }

protected:
  // property
  double mass_;

  // status (linear)
  Eigen::Vector3d com_{ 0., 0., 0. };
  Eigen::Vector3d momentum_{ 0., 0., 0. };

  // status (rotation)
  Eigen::Matrix3d rotation_{ Eigen::Matrix3d::Identity() };

  // simulation
  Eigen::Vector3d force_{ 0., 0., 0. };

private:
  std::shared_ptr<Shape> shape_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
