#ifndef SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_CYLINDER_H_
#define SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_CYLINDER_H_

#include "softphys/physics/object/primitive_object.h"

namespace softphys
{
class PrimitiveCylinder : public PrimitiveObject
{
public:
  PrimitiveCylinder() = delete;

  PrimitiveCylinder(double density, double radius, double height);

  ~PrimitiveCylinder();

  double Volume() override;

private:
  double radius_;
  double height_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_PRIMITIVE_CYLINDER_H_
