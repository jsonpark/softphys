#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
PrimitiveObject::PrimitiveObject(double density)
  : density_(density)
{
}

PrimitiveObject::PrimitiveObject(std::shared_ptr<model::Primitive> primitive, double density)
  : model_primitive_(primitive), density_(density)
{
}

PrimitiveObject::~PrimitiveObject() = default;
}
