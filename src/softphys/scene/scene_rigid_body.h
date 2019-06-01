#ifndef SOFTPHYS_SCENE_SCENE_RIGID_BODY_H_
#define SOFTPHYS_SCENE_SCENE_RIGID_BODY_H_

#include "softphys/scene/scene_object.h"

#include <vector>

#include <Eigen/Dense>

#include "softphys/scene/scene_primitive.h"

namespace softphys
{
namespace scene
{
class RigidBody : public Object
{
private:
  struct PrimitiveTransformed
  {
    std::shared_ptr<Primitive> primitive;
    Eigen::Affine3d transform;
  };

public:
  RigidBody();
  ~RigidBody();

  bool IsRigidBody() const noexcept override
  {
    return true;
  }

  void AddPrimitive(std::shared_ptr<Primitive> primitive, const Eigen::Vector3d& position, const Eigen::Quaterniond& orientation);

  const auto& Primitives() const
  {
    return primitives_;
  }

private:
  std::vector<PrimitiveTransformed> primitives_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_RIGID_BODY_H_
