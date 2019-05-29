#include "softphys/physics/object/ground.h"

namespace softphys
{
Ground::Ground(const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : normal_(normal), center_(center)
{
}

Ground::~Ground() = default;
}
