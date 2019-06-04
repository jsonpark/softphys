#include "softphys/physics/physics_loader.h"

#include <fstream>
#include <iostream>

#include "softphys/json/json.h"
#include "softphys/physics/object/sphere.h"
#include "softphys/physics/object/cube.h"
#include "softphys/model/physics/physics_sphere.h"
#include "softphys/model/physics/physics_cube.h"

namespace softphys
{
namespace physics
{
PhysicsLoader::PhysicsLoader() = default;

PhysicsLoader::~PhysicsLoader() = default;

std::shared_ptr<Physics> PhysicsLoader::LoadFromJson(const std::string& filename, std::shared_ptr<model::Modelset> models)
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
    return nullptr;
  }

  auto physics = std::make_shared<Physics>();

  // Gravity
  auto gravity = json.At("gravity").Get<Vector3d>();
  physics->SetGravity(gravity);

  // Timestep
  auto timestep= json.At("timestep").Get<double>();
  physics->SetTimestep(timestep);

  // Ground
  const auto& json_ground = json["ground"];
  auto ground_modelname = json_ground.At("model_name").Get<std::string>();
  auto ground_position = json_ground.At("position").Get<Vector3d>();
  auto ground_orientation = json_ground.At("orientation").Get<Quaterniond>();
  auto model_ground = models->GetModel(ground_modelname);

  Affine3d t;
  t.setIdentity();
  t.rotate(ground_orientation);
  // TODO:
  physics->CreateObject<Ground>(ground_modelname, t.matrix().block(0, 2, 3, 1), ground_position);

  // Objects
  const auto& objects = json["objects"];
  for (int i = 0; i < objects.Size(); i++)
  {
    const auto& json_object = objects[i];
    auto name = json_object.At("name").Get<std::string>();
    auto model_name = json_object.At("model_name").Get<std::string>();
    auto type = json_object.At("type").Get<std::string>();
    auto position = json_object.At("position").Get<Vector3d>();
    auto orientation = json_object.At("orientation").Get<Quaterniond>();

    if (type == "rigid_body")
    {
      auto physics_model = models->GetModel(model_name)->GetPhysics();

      if (physics_model->IsSphere())
      {
        auto sphere_model = std::static_pointer_cast<model::PhysicsSphere>(physics_model);
        auto sphere = physics->CreateObject<Sphere>(model_name, sphere_model->Radius(), sphere_model->Density());
        sphere->SetPosition(position);
        sphere->SetOrientation(orientation);
      }

      else if (physics_model->IsCube())
      {
        auto cube_model = std::static_pointer_cast<model::PhysicsCube>(physics_model);
        auto cube = physics->CreateObject<Cube>(model_name, cube_model->Size(), cube_model->Density());
        cube->SetPosition(position);
        cube->SetOrientation(orientation);
      }
    }
  }

  return physics;
}
}
}
