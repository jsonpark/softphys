#include "softphys/scene/scene_primitive.h"

namespace softphys
{
namespace scene
{
Primitive::Primitive(double density, int material)
  : density_(density), material_(material)
{
}

Primitive::~Primitive() = default;
}
}
