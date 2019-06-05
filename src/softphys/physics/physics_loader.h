#ifndef SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_
#define SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_

#include <memory>
#include <string>

#include "softphys/physics/physics.h"
#include "softphys/model/modelset.h"

namespace softphys
{
class Engine;

namespace physics
{
class PhysicsLoader
{
public:
  PhysicsLoader() = delete;
  PhysicsLoader(Engine* engine);
  ~PhysicsLoader();

  std::shared_ptr<Physics> LoadFromJson(const std::string& filename);

private:
  Engine* engine_;
};
}
}

#endif // SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_
