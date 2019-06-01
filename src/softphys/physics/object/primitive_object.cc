#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
PrimitiveObject::PrimitiveObject(std::shared_ptr<scene::Primitive> scene_primitive, double density)
  : scene_primitive_(scene_primitive), density_(density)
{
}

PrimitiveObject::~PrimitiveObject() = default;
}
