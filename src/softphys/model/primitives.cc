#include "softphys/model/primitives.h"

namespace softphys
{
namespace model
{
Primitives::Primitives(const std::string& name)
  : Model(name)
{
}

Primitives::~Primitives() = default;

void Primitives::AddPrimitive(const Affine3d& transform, std::shared_ptr<Primitive> primitive)
{
  transforms_.push_back(transform);
  primitives_.push_back(primitive);
}
}
}
