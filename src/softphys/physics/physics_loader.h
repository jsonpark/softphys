#ifndef SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_
#define SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_

#include <memory>
#include <string>

#include "softphys/physics/physics.h"
#include "softphys/scene/scene.h"

namespace softphys
{
class PhysicsLoader
{
public:
  PhysicsLoader();
  ~PhysicsLoader();

  std::shared_ptr<Physics> LoadFromJson(const std::string& filename, std::shared_ptr<scene::Scene> scene);

private:
};
}

#endif // SOFTPHYS_PHYSICS_PHYSICS_LOADER_H_
