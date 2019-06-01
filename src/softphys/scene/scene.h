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
  void AddMaterial(const Material& material);
  void AddObject(std::shared_ptr<Object> object);

  const auto& GetLights() const
  {
    return lights_;
  }

  const auto& GetObjects() const
  {
    return objects_;
  }

  auto GetObject(int idx) const
  {
    return objects_[idx];
  }

  const auto& GetMaterial(int idx)
  {
    return materials_[idx];
  }

private:
  std::vector<Light> lights_;
  std::vector<Material> materials_;
  std::vector<std::shared_ptr<Object>> objects_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_H_
