#ifndef SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
#define SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_

#include "softphys/physics/object/object.h"
#include "softphys/physics/object/primitive_object.h"

#include <vector>

#include <Eigen/StdVector>

#include "softphys/shape/shape.h"

namespace softphys
{
class RigidBody : public Object
{
private:
  using Affine3dVector = std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>>;

public:
  RigidBody();
  ~RigidBody();

  bool IsRigidBody() const noexcept override
  {
    return true;
  }

  void AttachPrimitive(std::shared_ptr<PrimitiveObject> primitive, const Eigen::Affine3d& transform);

  template<typename PrimitiveObjectType, typename... Ts>
  std::shared_ptr<PrimitiveObjectType> CreatePrimitive(const Eigen::Affine3d& transform, Ts&&... args)
  {
    auto primitive = std::make_shared<PrimitiveObjectType>(std::forward<Ts>(args)...);
    AttachPrimitive(primitive, transform);

    return primitive;
  }

  void SetPosition(const Eigen::Vector3d& position)
  {
    position_ = position;
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

  const auto& GetRotation()
  {
    return rotation_;
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

  const auto& GetPrimitives() const noexcept
  {
    return primitives_;
  }

  const auto& GetTransforms() const noexcept
  {
    return transforms_;
  }

  Eigen::Vector3d GetVelocity() const
  {
    return momentum_ / mass_;
  }

protected:
  // property
  double mass_ = 0.;
  Eigen::Vector3d com_{ 0., 0., 0. };

  // status (linear)
  Eigen::Vector3d position_{ 0., 0., 0. };
  Eigen::Vector3d momentum_{ 0., 0., 0. };

  // status (rotation)
  Eigen::Matrix3d rotation_{ Eigen::Matrix3d::Identity() };

  // simulation
  Eigen::Vector3d force_{ 0., 0., 0. };

private:
  std::vector<std::shared_ptr<PrimitiveObject>> primitives_;
  Affine3dVector transforms_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
