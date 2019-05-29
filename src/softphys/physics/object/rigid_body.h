#ifndef SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
#define SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_

#include "softphys/physics/object/object.h"

namespace softphys
{
class RigidBody : public Object
{
public:
  RigidBody() = delete;
  RigidBody(double mass);
  ~RigidBody();

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
  void Simulate(double time) override;

protected:
  // status
  double mass_;
  Eigen::Vector3d com_{ 0., 0., 0. };
  Eigen::Vector3d momentum_{ 0., 0., 0. };

  // simulation
  Eigen::Vector3d force_{ 0., 0., 0. };

private:
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_RIGID_BODY_H_
