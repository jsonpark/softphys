#ifndef SOFTPHYS_SCENE_SCENE_LOADER_H_
#define SOFTPHYS_SCENE_SCENE_LOADER_H_

#include <vector>

#include "softphys/scene/scene.h"

namespace softphys
{
namespace scene
{
class SceneLoader
{
public:
  SceneLoader();
  ~SceneLoader();

  std::shared_ptr<Scene> LoadFromJson(const std::string& filename);

private:
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_LOADER_H_
