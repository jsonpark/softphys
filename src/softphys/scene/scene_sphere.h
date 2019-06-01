#ifndef SOFTPHYS_SCENE_SCENE_SPHERE_H_
#define SOFTPHYS_SCENE_SCENE_SPHERE_H_

#include "softphys/scene/scene_primitive.h"

namespace softphys
{
namespace scene
{
class Sphere : public Primitive
{
public:
  Sphere() = delete;
  Sphere(double density, int material, double radius);
  ~Sphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  auto Radius()
  {
    return radius_;
  }

private:
  double radius_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_SPHERE_H_
