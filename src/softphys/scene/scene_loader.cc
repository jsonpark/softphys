#include "softphys/scene/scene_loader.h"

#include "softphys/json/json.h"
#include "softphys/scene/scene_rigid_body.h"
#include "softphys/scene/scene_ground.h"
#include "softphys/scene/scene_sphere.h"
#include "softphys/scene/scene_plane.h"

#include <fstream>
#include <iostream>

namespace softphys
{
namespace scene
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

Eigen::Vector3d JsonArrayToVector3d(const Json& json)
{
  Eigen::Vector3d v;
  v(0) = json[0].Get<double>();
  v(1) = json[1].Get<double>();
  v(2) = json[2].Get<double>();
  return v;
}

Eigen::Vector4d JsonArrayToVector4d(const Json& json)
{
  Eigen::Vector4d v;
  v(0) = json[0].Get<double>();
  v(1) = json[1].Get<double>();
  v(2) = json[2].Get<double>();
  v(3) = json[3].Get<double>();
  return v;
}

Eigen::Quaterniond JsonArrayToQuaternion(const Json& json)
{
  Eigen::Quaterniond v;
  v.w() = json[0].Get<double>();
  v.x() = json[1].Get<double>();
  v.y() = json[2].Get<double>();
  v.z() = json[3].Get<double>();
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

  // Material
  const auto& materials = json["materials"];
  for (int i = 0; i < materials.Size(); i++)
  {
    const auto& json_material = materials[i];
    Material material;

    material.name = json_material.At("name").Get<std::string>();

    if (json_material.HasKey("preset"))
      material.preset = json_material.At("preset").Get<std::string>();
    else
    {
      material.ambient = JsonArrayToVector3f(json_material.At("ambient"));
      material.diffuse = JsonArrayToVector3f(json_material.At("diffuse"));
      material.specular = JsonArrayToVector3f(json_material.At("specular"));
      material.shininess = json_material.At("shininess").Get<float>();
    }

    scene->AddMaterial(material);
  }

  // Objects
  const auto& objects = json["objects"];
  for (int i = 0; i < objects.Size(); i++)
  {
    const auto& json_object = objects[i];
    auto type = json_object.At("type").Get<std::string>();

    if (type == "ground")
    {
      auto material = json_object.At("material").Get<int>();

      scene->AddObject(std::make_shared<Ground>(material));
    }

    if (type == "rigid_body")
    {
      const auto& primitives = json_object.At("primitives");
      auto rigid_body = std::make_shared<RigidBody>();

      for (int j = 0; j < primitives.Size(); j++)
      {
        const auto& json_primitive = primitives[j];
        auto primitive_type = json_primitive.At("type").Get<std::string>();
        auto material = json_primitive.At("material").Get<int>();
        auto density = json_primitive.At("density").Get<double>();
        auto position = JsonArrayToVector3d(json_primitive.At("position"));
        auto orientation = JsonArrayToQuaternion(json_primitive.At("orientation"));

        if (primitive_type == "sphere")
        {
          auto radius = json_primitive.At("radius").Get<double>();

          rigid_body->AddPrimitive(std::make_shared<Sphere>(density, material, radius), position, orientation);
        }
      }

      scene->AddObject(rigid_body);
    }
  }

  return scene;
}
}
}
