#include "softphys/model/primitive/sphere.h"

namespace softphys
{
namespace model
{
Sphere::Sphere(const std::string& material_name, double density, double radius)
  : Primitive(material_name, density),
  radius_(radius)
{
}

Sphere::~Sphere() = default;
}
}
