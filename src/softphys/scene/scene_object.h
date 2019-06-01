#ifndef SOFTPHYS_SCENE_SCENE_OBJECT_H_
#define SOFTPHYS_SCENE_SCENE_OBJECT_H_

#include <Eigen/Dense>

namespace softphys
{
namespace scene
{
class Object
{
public:
  Object();
  virtual ~Object();

  virtual bool IsGround() const noexcept
  {
    return false;
  }

  virtual bool IsRigidBody() const noexcept
  {
    return false;
  }

private:
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_OBJECT_H_
