#ifndef SOFTPHYS_SHAPE_SPHERE_H_
#define SOFTPHYS_SHAPE_SPHERE_H_

#include "softphys/shape/shape.h"

namespace softphys
{
class Sphere : public Shape
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

#endif // SOFTPHYS_SHAPE_SPHERE_H_
