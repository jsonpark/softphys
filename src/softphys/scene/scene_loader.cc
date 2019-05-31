#include "softphys/scene/scene_loader.h"

#include "softphys/json/json.h"

#include <fstream>
#include <iostream>

namespace softphys
{
namespace
{
Eigen::Vector3f JsonArrayToVector3f(const Json& json)
{
  Eigen::Vector3f v;
  v(0) = json[0].Get<float>();
  v(1) = json[1].Get<float>();
  v(2) = json[2].Get<float>();
  return v;
}
}

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

    light.position = JsonArrayToVector3f(json_light.At("position"));
    light.ambient = JsonArrayToVector3f(json_light.At("ambient"));
    light.diffuse = JsonArrayToVector3f(json_light.At("diffuse"));
    light.specular = JsonArrayToVector3f(json_light.At("specular"));

    scene->AddLight(light);
  }

  return scene;
}
}
