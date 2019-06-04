#ifndef SOFTPHYS_PHYSICS_OBJECT_CUBE_H_
#define SOFTPHYS_PHYSICS_OBJECT_CUBE_H_

#include "softphys/physics/object/rigid_body.h"

namespace softphys
{
namespace physics
{
class Cube : public RigidBody
{
public:
  Cube() = delete;

  Cube(const Vector3d& size, double density);
  Cube(const std::string& model_name, const Vector3d& size, double density);

  ~Cube();

  bool IsCube() const noexcept override
  {
    return true;
  }

  double Volume() const;

  auto Size() const noexcept
  {
    return size_;
  }

private:
  double density_;
  Vector3d size_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_CUBE_H_
