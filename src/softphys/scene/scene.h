#ifndef SOFTPHYS_SCENE_SCENE_H_
#define SOFTPHYS_SCENE_SCENE_H_

#include <vector>
#include <unordered_map>

#include "softphys/viewer/light.h"
#include "softphys/viewer/material.h"

namespace softphys
{
class Scene
{
public:
  static const int max_lights = 8;

public:
  Scene();
  ~Scene();

  void AddLight(const Light& light);
  void AddMaterial(const std::string& name, const Material& material);

  const auto& GetLights() const
  {
    return lights_;
  }

private:
  std::vector<Light> lights_;
  std::unordered_map<std::string, Material> materials_;
};
}

#endif // SOFTPHYS_SCENE_SCENE_H_
