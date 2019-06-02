#ifndef SOFTPHYS_SCENE_SCENE_H_
#define SOFTPHYS_SCENE_SCENE_H_

#include <vector>
#include <unordered_map>
#include <memory>

#include "softphys/viewer/light.h"
#include "softphys/viewer/material.h"
#include "softphys/scene/scene_primitive.h"
#include "softphys/scene/scene_object.h"

namespace softphys
{
namespace scene
{
class Scene
{
public:
  static const int max_lights = 8;

public:
  Scene();
  ~Scene();

  void AddLight(const Light& light);

  const auto& GetLights() const
  {
    return lights_;
  }

private:
  std::vector<Light> lights_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_H_
