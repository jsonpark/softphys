#include "softphys/model/primitive/primitive.h"

namespace softphys
{
namespace model
{
Primitive::Primitive() = default;

Primitive::Primitive(const std::string& material_name, double density)
  : material_name_(material_name), density_(density)
{
}

Primitive::~Primitive() = default;
}
}
