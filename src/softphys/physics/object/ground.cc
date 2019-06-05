#include "softphys/physics/object/ground.h"

namespace softphys
{
namespace physics
{
Ground::Ground(const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : Object(),
  normal_(normal), center_(center)
{
}

Ground::~Ground() = default;
}
}
