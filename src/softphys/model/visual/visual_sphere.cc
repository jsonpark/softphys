#include "softphys/model/visual/visual_sphere.h"

namespace softphys
{
namespace model
{
VisualSphere::VisualSphere(const std::string& material_name, double radius)
  : Visual(material_name),
  radius_(radius)
{
}

VisualSphere::~VisualSphere() = default;
}
}
