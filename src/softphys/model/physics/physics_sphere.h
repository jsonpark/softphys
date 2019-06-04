#ifndef SOFTPHYS_MODEL_PHYSICS_PHYSICS_SPHERE_H_
#define SOFTPHYS_MODEL_PHYSICS_PHYSICS_SPHERE_H_

#include "softphys/model/physics/physics.h"

namespace softphys
{
namespace model
{
class PhysicsSphere : public Physics
{
public:
  PhysicsSphere() = delete;
  PhysicsSphere(double radius, double density);
  ~PhysicsSphere();

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
  double radius_;
};
}
}

#endif // SOFTPHYS_MODEL_PHYSICS_PHYSICS_SPHERE_H_
