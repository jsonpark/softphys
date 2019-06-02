#include "softphys/physics/physics_loader.h"

#include <fstream>
#include <iostream>

#include "softphys/json/json.h"
#include "softphys/model/primitives.h"
#include "softphys/model/primitive/sphere.h"
#include "softphys/physics/object/primitive_sphere.h"

namespace softphys
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

  // Ground
  const auto& json_ground = json["ground"];
  auto ground_modelname = json_ground.At("model_name").Get<std::string>();
  auto ground_position = json_ground.At("position").Get<Vector3d>();
  auto ground_orientation = json_ground.At("orientation").Get<Quaterniond>();
  auto model_ground = models->GetModel(ground_modelname);

  Affine3d t;
  t.setIdentity();
  t.rotate(ground_orientation);
  physics->CreateObject<SimulationGround>(ground_modelname, t.matrix().block(0, 2, 3, 1), ground_position);

  // Objects
  const auto& objects = json["objects"];
  for (int i = 0; i < objects.Size(); i++)
  {
    const auto& json_object = objects[i];
    auto model_name = json_object.At("model_name").Get<std::string>();
    auto type = json_object.At("type").Get<std::string>();
    auto position = json_object.At("position").Get<Vector3d>();
    auto orientation = json_object.At("orientation").Get<Quaterniond>();

    if (type == "rigid_body")
    {
      auto model = models->GetModel(model_name);

      if (model->IsPrimitives())
      {
        auto rigid_body = physics->CreateObject<RigidBody>(model_name);
        rigid_body->SetPosition(position);
        rigid_body->SetOrientation(orientation);

        auto model_primitives = std::static_pointer_cast<model::Primitives>(model);
        for (int i = 0; i < model_primitives->NumPrimitives(); i++)
        {
          auto primitive = model_primitives->GetPrimitive(i);
          const auto& transform = model_primitives->GetTransform(i);

          if (primitive->IsSphere())
          {
            auto sphere = std::static_pointer_cast<model::Sphere>(primitive);
            rigid_body->CreatePrimitive<PrimitiveSphere>(transform, sphere, sphere->Density(), sphere->Radius());
          }
        }
      }
    }
  }

  return physics;
}
}
