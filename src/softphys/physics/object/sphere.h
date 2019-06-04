#ifndef SOFTPHYS_PHYSICS_OBJECT_SPHERE_H_
#define SOFTPHYS_PHYSICS_OBJECT_SPHERE_H_

#include "softphys/physics/object/rigid_body.h"

namespace softphys
{
namespace physics
{
class Sphere : public RigidBody
{
public:
  Sphere() = delete;

  Sphere(double radius, double density);
  Sphere(const std::string& model_name, double radius, double density);

  ~Sphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  double Volume() const;

  auto Radius() const noexcept
  {
    return radius_;
  }

private:
  double density_;
  double radius_;
};
}
}

#endif // SOFTPHYS_PHYSICS_OBJECT_SPHERE_H_
