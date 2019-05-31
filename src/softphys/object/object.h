#ifndef SOFTPHYS_OBJECT_OBJECT_H_
#define SOFTPHYS_OBJECT_OBJECT_H_

#include <Eigen/Dense>

#include "softphys/viewer/material.h"

namespace softphys
{
class Object
{
public:
  Object();
  virtual ~Object();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual bool IsPlane() const noexcept
  {
    return false;
  }

  void SetMaterial(const Material& material)
  {
    material_ = material;
  }

private:
  Material material_;
  Eigen::Affine3d transform_; // transform from the object's parent
};
}

#endif // SOFTPHYS_OBJECT_OBJECT_H_
