#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/viewer/model_viewer.h"

#include <iostream>

int main()
{
  softphys::Engine engine;
  engine.LoadModels("..\\data\\models.json");
  engine.LoadPhysics("..\\data\\physics.json");

  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->LoadScene("..\\data\\scene.json");

  auto model_viewer = engine.CreateEngineWindow<softphys::ModelViewer>(400, 200, 1024, 768);
  model_viewer->LoadScene("..\\data\\scene.json");

  engine.Run();

  return 0;
}
