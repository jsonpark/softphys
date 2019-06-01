#ifndef SOFTPHYS_SCENE_SCENE_GROUND_H_
#define SOFTPHYS_SCENE_SCENE_GROUND_H_

#include "softphys/scene/scene_object.h"

#include <Eigen/Dense>

namespace softphys
{
namespace scene
{
class Ground : public Object
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Ground() = delete;
  Ground(int material);
  ~Ground();

  bool IsGround() const noexcept override
  {
    return true;
  }

private:
  int material_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_GROUND_H_
