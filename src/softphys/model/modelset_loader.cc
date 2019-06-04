#include "softphys/model/modelset_loader.h"

#include <fstream>
#include <iostream>

#include "softphys/json/json.h"
#include "softphys/model/visual/visual_sphere.h"
#include "softphys/model/visual/visual_cube.h"
#include "softphys/model/physics/physics_sphere.h"
#include "softphys/model/physics/physics_cube.h"

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
      if (json_material.HasKey("diffuse"))
      {
        auto ambient = json_material.At("ambient").Get<Vector3f>();
        auto diffuse = json_material.At("diffuse").Get<Vector3f>();
        auto specular = json_material.At("specular").Get<Vector3f>();
        auto shininess = json_material.At("shininess").Get<float>();

        modelset->CreateMaterial(name, ambient, diffuse, specular, shininess);
      }
      else
      {
        // TODO: material has a diffuse texture
      }
    }
  }

  // Models
  const auto& json_models = json["models"];
  for (int i = 0; i < json_models.Size(); i++)
  {
    const auto& json_model = json_models[i];
    auto name = json_model.At("name").Get<std::string>();
    const auto& json_visuals = json_model.At("visuals");
    const auto& json_physics = json_model.At("physics");

    auto model = modelset->CreateModel<Model>(name);

    // Visuals
    const auto& visual_type = json_visuals.At("type").Get<std::string>();

    if (visual_type == "sphere")
    {
      auto radius = json_visuals.At("radius").Get<double>();
      auto material_name = json_visuals.At("material").Get<std::string>();

      auto visual_sphere = std::make_shared<VisualSphere>(material_name, radius);

      model->SetVisual(visual_sphere);
    }

    if (visual_type == "cube")
    {
      auto size = json_visuals.At("size").Get<Vector3d>();
      auto material_name = json_visuals.At("material").Get<std::string>();

      auto visual_cube = std::make_shared<VisualCube>(material_name, size.cast<float>());

      model->SetVisual(visual_cube);
    }

    // Physics
    const auto& physics_type = json_visuals.At("type").Get<std::string>();

    if (physics_type == "sphere")
    {
      auto radius = json_physics.At("radius").Get<double>();
      auto density = json_physics.At("density").Get<double>();

      auto physics_sphere = std::make_shared<PhysicsSphere>(radius, density);

      model->SetPhysics(physics_sphere);
    }

    else if (physics_type == "cube")
    {
      auto size = json_physics.At("size").Get<Vector3d>();
      auto density = json_physics.At("density").Get<double>();

      auto physics_cube = std::make_shared<PhysicsCube>(size, density);

      model->SetPhysics(physics_cube);
    }

    modelset->AddModel(model);
  }

  return modelset;
}
}
}
