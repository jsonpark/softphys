#ifndef SOFTPHYS_OBJECT_SPHERE_H_
#define SOFTPHYS_OBJECT_SPHERE_H_

#include "softphys/object/object.h"

namespace softphys
{
class Sphere : public Object
{
public:
  Sphere();
  Sphere(double radius);

  ~Sphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  auto Radius() const noexcept
  {
    return radius_;
  }

private:
  double radius_ = 1.;
};
}

#endif // SOFTPHYS_OBJECT_SPHERE_H_
