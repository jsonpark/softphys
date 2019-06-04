#include "softphys/physics/object/ground.h"

namespace softphys
{
namespace physics
{
Ground::Ground(const std::string& model_name, const Eigen::Vector3d& normal, const Eigen::Vector3d& center)
  : Object(model_name),
  normal_(normal), center_(center)
{
}

Ground::~Ground() = default;
}
}
