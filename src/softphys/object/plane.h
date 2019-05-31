#ifndef SOFTPHYS_OBJECT_PLANE_H_
#define SOFTPHYS_OBJECT_PLANE_H_

#include "softphys/object/object.h"

namespace softphys
{
class Plane : public Object
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

#endif // SOFTPHYS_OBJECT_PLANE_H_
