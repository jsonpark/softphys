#ifndef SOFTPHYS_PHYSICS_PHYSICS_H_
#define SOFTPHYS_PHYSICS_PHYSICS_H_

#include <memory>
#include <vector>

#include "softphys/physics/object/object.h"

namespace softphys
{
class Physics
{
public:
  Physics();
  ~Physics();

  template<typename ObjectType, typename... Ts>
  std::shared_ptr<ObjectType> CreateObject(Ts&& ... args)
  {
    auto object = std::make_shared<ObjectType>(std::forward<Ts>(args)...);

    objects_.push_back(object);

    return object;
  }

  auto GetTime() const noexcept
  {
    return time_;
  }

  void SetGravity(double g);
  void SetGravity(const Eigen::Vector3d& g);
  void SetEarthGravity();

  void Simulate(double time);

  const auto& GetObjects() const
  {
    return objects_;
  }

private:
  double time_ = 0.;

  Eigen::Vector3d gravity_{ 0., 0., 0. };

  std::vector<std::shared_ptr<Object>> objects_;
};
}

#endif // SOFTPHYS_PHYSICS_PHYSICS_H_
