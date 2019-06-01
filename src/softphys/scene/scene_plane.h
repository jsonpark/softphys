#ifndef SOFTPHYS_SCENE_SCENE_PLANE_H_
#define SOFTPHYS_SCENE_SCENE_PLANE_H_

#include "softphys/scene/scene_primitive.h"

#include <Eigen/Dense>

namespace softphys
{
namespace scene
{
class Plane : public Primitive
{
public:
  Plane() = delete;
  Plane(int material);
  ~Plane();

  bool IsPlane() const noexcept override
  {
    return true;
  }

private:
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_PLANE_H_
