#include "softphys/physics/contact/moving_primitive.h"

namespace softphys
{
MovingPrimitive::MovingPrimitive(std::shared_ptr<PrimitiveObject> primitive, const Eigen::Vector3d& velocity)
  : primitive_(primitive), velocity_(velocity)
{
}

MovingPrimitive::~MovingPrimitive() = default;
}
