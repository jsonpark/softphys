#ifndef SOFTPHYS_PHYSICS_OBJECT_GROUND_H_
#define SOFTPHYS_PHYSICS_OBJECT_GROUND_H_

#include "softphys/physics/object/object.h"

#include "softphys/data/eigen.h"

namespace softphys
{
namespace physics
{
class Ground : public Object
{
public:
  Ground() = delete;
  Ground(const Vector3d& normal, const Vector3d& center);
  ~Ground();

  bool IsGround() const noexcept override
  {
    return true;
  }

  const auto& Normal() const noexcept
  {
    return normal_;
  }

  const auto& Center() const noexcept
  {
    return center_;
  }

private:
  Vector3d normal_;
  Vector3d center_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_GROUND_H_
