#include "softphys/model/modelset_loader.h"

#include <fstream>
#include <iostream>

#include "softphys/json/json.h"
#include "softphys/model/ground.h"
#include "softphys/model/primitives.h"
#include "softphys/model/primitive/sphere.h"

namespace softphys
{
namespace model
{
ModelsetLoader::ModelsetLoader() = default;

ModelsetLoader::~ModelsetLoader() = default;

std::shared_ptr<Modelset> ModelsetLoader::LoadFromJson(const std::string& filename)
{
  std::ifstream in(filename);
  if (!in.is_open())
  {
    return nullptr;
  }

  Json json;
  try
  {
    in >> json;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
    return nullptr;
  }

  auto modelset = std::make_shared<Modelset>();

  // Materials
  const auto& json_materials = json["materials"];
  for (int i = 0; i < json_materials.Size(); i++)
  {
    const auto& json_material = json_materials[i];
    auto name = json_material.At("name").Get<std::string>();

    if (json_material.HasKey("preset"))
    {
      // TODO
    }
    else
    {
      auto ambient = json_material.At("ambient").Get<Vector3f>();
      auto diffuse = json_material.At("diffuse").Get<Vector3f>();
      auto specular = json_material.At("specular").Get<Vector3f>();
      auto shininess = json_material.At("shininess").Get<float>();

      modelset->CreateMaterial(name, ambient, diffuse, specular, shininess);
    }
  }

  // Models
  const auto& json_models = json["models"];
  for (int i = 0; i < json_models.Size(); i++)
  {
    const auto& json_model = json_models[i];
    auto name = json_model.At("name").Get<std::string>();
    auto type = json_model.At("type").Get<std::string>();

    if (type == "ground")
    {
      const auto& json_visuals = json_model.At("visuals");
      auto material_name = json_visuals.At("material").Get<std::string>();

      auto ground = modelset->CreateModel<Ground>(name);
      ground->SetMaterialName(material_name);
    }

    else if (type == "primitives")
    {
      auto primitives = modelset->CreateModel<Primitives>(name);

      const auto& json_primitives = json_model.At("primitives");
      for (int j = 0; j < json_primitives.Size(); j++)
      {
        const auto& json_primitive = json_primitives[j];
        auto primitive_type = json_primitive.At("type").Get<std::string>();
        auto position = json_primitive.At("position").Get<Vector3d>();
        auto orientation = json_primitive.At("orientation").Get<Quaterniond>();
        auto material_name = json_primitive.At("visuals").At("material").Get<std::string>();
        auto density = json_primitive.At("physics").At("density").Get<double>();

        Affine3d transform;
        transform.setIdentity();
        transform.rotate(orientation).translate(position);

        if (primitive_type == "sphere")
        {
          auto radius = json_primitive.At("radius").Get<double>();

          primitives->AddPrimitive(transform, std::make_shared<Sphere>(material_name, density, radius));
        }
      }

      modelset->AddModel(primitives);
    }
  }

  return modelset;
}
}
}
