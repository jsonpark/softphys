#ifndef SOFTPHYS_PHYSICS_CONTACT_MOVING_PRIMITIVE_H_
#define SOFTPHYS_PHYSICS_CONTACT_MOVING_PRIMITIVE_H_

#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
class MovingPrimitive
{
public:
  MovingPrimitive() = delete;
  MovingPrimitive(std::shared_ptr<PrimitiveObject> primitive, const Eigen::Vector3d& velocity);

  ~MovingPrimitive();

  auto Primitive() const
  {
    return primitive_;
  }

  const auto& Velocity() const
  {
    return velocity_;
  }

private:
  std::shared_ptr<PrimitiveObject> primitive_;
  Eigen::Vector3d velocity_; // in world coordinate
};
}

#endif // SOFTPHYS_PHYSICS_CONTACT_MOVING_PRIMITIVE_H_
