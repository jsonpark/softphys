#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/physics/physics.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/simulation_ground.h"
#include "softphys/physics/object/primitive_sphere.h"
#include "softphys/object/sphere.h"
#include "softphys/viewer/light.h"

#include <iostream>

int main()
{
  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->LoadScene("..\\data\\scene.json");
  viewer->LoadPhysics("..\\data\\physics.json");
  engine.Run();

  return 0;
}
