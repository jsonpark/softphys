#include "softphys/engine/engine.h"
#include "viewer/viewer.h"

#include <memory>

int main()
{
  softphys::Engine engine;
  {
    auto window1 = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 800, 600);
  }
  engine.Run();

  return 0;
}
