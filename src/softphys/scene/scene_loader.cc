#include "softphys/scene/scene_loader.h"

#include "softphys/json/json.h"

#include <fstream>
#include <iostream>

namespace softphys
{
namespace scene
{
SceneLoader::SceneLoader() = default;

SceneLoader::~SceneLoader() = default;

std::shared_ptr<Scene> SceneLoader::LoadFromJson(const std::string& filename)
{
  std::ifstream in(filename);
  if (!in.is_open())
    return nullptr;

  Json json;
  try
  {
    in >> json;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  in.close();

  auto scene = std::make_shared<Scene>();

  // Light
  const auto& lights = json["lights"];
  for (int i = 0; i < lights.Size(); i++)
  {
    const auto& json_light = lights[i];
    Light light;

    auto type = json_light.At("type").Get<std::string>();
    if (type == "directional")
      light.type = Light::Type::Directional;
    else if (type == "point")
      light.type = Light::Type::Point;
    else
    {
      std::cout << "Scene Loader: light type is neighter directional nor point" << std::endl;
      continue;
    }

    light.position = json_light.At("position").Get<Vector3f>();
    light.ambient = json_light.At("ambient").Get<Vector3f>();
    light.diffuse = json_light.At("diffuse").Get<Vector3f>();
    light.specular = json_light.At("specular").Get<Vector3f>();

    scene->AddLight(light);
  }

  return scene;
}
}
}
