#include "softphys/physics/physics_loader.h"

#include <fstream>
#include <iostream>

#include "softphys/json/json.h"
#include "softphys/scene/scene_rigid_body.h"
#include "softphys/scene/scene_sphere.h"
#include "softphys/physics/object/primitive_sphere.h"

namespace softphys
{
// TODO: make these utility functions common among other .cc files
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

PhysicsLoader::PhysicsLoader() = default;

PhysicsLoader::~PhysicsLoader() = default;

std::shared_ptr<Physics> PhysicsLoader::LoadFromJson(const std::string& filename, std::shared_ptr<scene::Scene> scene)
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
  auto gravity = JsonArrayToVector3d(json.At("gravity"));
  physics->SetGravity(gravity);

  // Ground
  const auto& json_ground = json["ground"];
  auto ground_id = json_ground.At("id").Get<int>();
  auto ground_position = JsonArrayToVector3d(json_ground.At("position"));
  auto ground_orientation = JsonArrayToQuaternion(json_ground.At("orientation"));
  auto scene_ground = scene->GetObject(ground_id);

  Eigen::Affine3d t;
  t.setIdentity();
  t.rotate(ground_orientation);
  physics->CreateObject<SimulationGround>(scene_ground, t.matrix().block(0, 2, 3, 1), ground_position);

  // Objects
  const auto& objects = json["objects"];
  for (int i = 0; i < objects.Size(); i++)
  {
    const auto& json_object = objects[i];
    auto id = json_object.At("id").Get<int>();
    auto position = JsonArrayToVector3d(json_object.At("position"));
    auto orientation = JsonArrayToQuaternion(json_object.At("orientation"));

    auto object = scene->GetObject(id);
    if (object->IsRigidBody())
    {
      auto rigid_body = physics->CreateObject<RigidBody>(object);
      rigid_body->SetPosition(position);
      rigid_body->SetOrientation(orientation);

      auto scene_rigid_body = std::static_pointer_cast<scene::RigidBody>(object);
      for (const auto& primitive_transform : scene_rigid_body->Primitives())
      {
        auto primitive = primitive_transform.primitive;
        const auto& transform = primitive_transform.transform;

        if (primitive->IsSphere())
        {
          auto sphere = std::static_pointer_cast<scene::Sphere>(primitive);
          rigid_body->CreatePrimitive<PrimitiveSphere>(transform, sphere, sphere->Density(), sphere->Radius());
        }
      }
    }
  }

  return physics;
}
}
