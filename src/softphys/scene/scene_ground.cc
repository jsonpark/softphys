#include "softphys/scene/scene_ground.h"

namespace softphys
{
namespace scene
{
Ground::Ground(int material)
  : Object(),
  material_(material)
{
}

Ground::~Ground() = default;
}
}
