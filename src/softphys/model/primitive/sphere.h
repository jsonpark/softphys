#ifndef SOFTPHYS_MODEL_PRIMITIVE_SPHERE_H_
#define SOFTPHYS_MODEL_PRIMITIVE_SPHERE_H_

#include "softphys/model/primitive/primitive.h"

namespace softphys
{
namespace model
{
class Sphere : public Primitive
{
public:
  Sphere() = delete;
  Sphere(const std::string& material_name, double density, double radius);
  ~Sphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  void SetRadius(double radius)
  {
    radius_ = radius;
  }

  auto Radius() const
  {
    return radius_;
  }

private:
  double radius_;
};
}
}

#endif // SOFTPHYS_MODEL_PRIMITIVE_SPHERE_H_
