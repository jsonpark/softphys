#include "softphys/physics/object/ground.h"

namespace softphys
{
namespace physics
{
Ground::Ground(const Vector3d& normal, const Vector3d& center)
  : Object(),
  normal_(normal), center_(center)
{
}

Ground::~Ground() = default;
}
}
