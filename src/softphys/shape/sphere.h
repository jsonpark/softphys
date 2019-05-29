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
  Sphere(double radius, const Eigen::Vector3d& center);

  ~Sphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  auto Radius() const noexcept
  {
    return radius_;
  }

  const auto& Center() const noexcept
  {
    return center_;
  }

private:
  double radius_ = 1.;
  Eigen::Vector3d center_{ 0., 0., 0. };
};
}

#endif // SOFTPHYS_SHAPE_SPHERE_H_
