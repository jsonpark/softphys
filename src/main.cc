#include "softphys/engine.h"
#include "softphys/viewer/viewer_window.h"
#include "softphys/viewer/model_viewer.h"

#include <iostream>

int main()
{
  softphys::Engine engine;
  engine.LoadModels("..\\data\\models.json");
  engine.LoadPhysics("..\\data\\physics.json");

  auto viewer = engine.CreateEngineWindow<softphys::ViewerWindow>("Physics Simulator", 200, 200, 1024, 768);
  viewer->LoadScene("..\\data\\scene.json");

  engine.Run();

  return 0;
}
