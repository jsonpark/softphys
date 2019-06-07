#include "softphys/engine.h"
#include "softphys/viewer/painter.h"
#include "softphys/viewer/model_viewer.h"

#include <iostream>

int main()
{
  softphys::Engine engine;
  engine.LoadModels("..\\data\\models.json");
  engine.LoadPhysics("..\\data\\physics.json");

  auto viewer = engine.CreateEngineWindow<softphys::Painter>("Physics Simulator", 200, 200, 1224, 768);
  viewer->LoadScene("..\\data\\scene.json");

  engine.Run();

  return 0;
}
