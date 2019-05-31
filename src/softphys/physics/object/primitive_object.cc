#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
PrimitiveObject::PrimitiveObject(double density)
  : density_(density)
{
}

PrimitiveObject::~PrimitiveObject() = default;
}
