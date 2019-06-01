#include "softphys/scene/scene_plane.h"

namespace softphys
{
namespace scene
{
Plane::Plane(int material)
  : Primitive(-1., material)
{
}

Plane::~Plane() = default;
}
}
