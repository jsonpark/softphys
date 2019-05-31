#ifndef SOFTPHYS_SHAPE_PLANE_H_
#define SOFTPHYS_SHAPE_PLANE_H_

#include "softphys/shape/shape.h"

namespace softphys
{
class Plane : public Shape
{
public:
  Plane();
  Plane(const Eigen::Vector4d& equation);
  ~Plane();

  bool IsPlane() const noexcept override
  {
    return true;
  }

  Eigen::Vector3d Normal();

private:
  Eigen::Vector4d equation_{ 0., 0., 1., 0. };
};
}

#endif // SOFTPHYS_SHAPE_PLANE_H_
