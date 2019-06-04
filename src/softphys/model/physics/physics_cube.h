#ifndef SOFTPHYS_MODEL_PHYSICS_PHYSICS_CUBE_H_
#define SOFTPHYS_MODEL_PHYSICS_PHYSICS_CUBE_H_

#include "softphys/model/physics/physics.h"

#include "softphys/data/eigen.h"

namespace softphys
{
namespace model
{
class PhysicsCube : public Physics
{
public:
  PhysicsCube() = delete;
  PhysicsCube(const Vector3d& size, double density);
  ~PhysicsCube();

  bool IsCube() const noexcept override
  {
    return true;
  }

  void SetSize(const Vector3d& size)
  {
    size_ = size;
  }

  auto Size() const
  {
    return size_;
  }

  void SetDensity(double density)
  {
    density_ = density;
  }

  auto Density() const
  {
    return density_;
  }

private:
  double density_;
  Vector3d size_;
};
}
}

#endif // SOFTPHYS_MODEL_PHYSICS_PHYSICS_CUBE_H_
