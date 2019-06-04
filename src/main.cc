#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"

#include <iostream>

int main()
{
  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->LoadModels("..\\data\\models.json");
  viewer->LoadScene("..\\data\\scene.json");
  viewer->LoadPhysics("..\\data\\physics.json");
  engine.Run();

  return 0;
}
