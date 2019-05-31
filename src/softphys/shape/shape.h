#ifndef SOFTPHYS_SHAPE_SHAPE_H_
#define SOFTPHYS_SHAPE_SHAPE_H_

#include <Eigen/Dense>

namespace softphys
{
class Shape
{
public:
  Shape();
  virtual ~Shape();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual bool IsPlane() const noexcept
  {
    return false;
  }

private:
};
}

#endif // SOFTPHYS_SHAPE_SHAPE_H_
