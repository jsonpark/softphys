#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/physics/physics.h"

#include <memory>

int main()
{
  auto physics = std::make_unique<softphys::Physics>();

  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 800, 600);
  viewer->DisplayPhysicsScene(std::move(physics));
  engine.Run();

  return 0;
}
