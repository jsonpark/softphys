#include "softphys/model/visual/visual_cube.h"

namespace softphys
{
namespace model
{
VisualCube::VisualCube(const std::string& material_name, const Vector3f& size)
  : Visual(material_name),
  size_(size)
{
}

VisualCube::~VisualCube() = default;
}
}
