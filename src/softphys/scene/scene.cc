#include "softphys/scene/scene.h"

namespace softphys
{
namespace scene
{
Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::AddLight(const Light& light)
{
  lights_.push_back(light);
}

void Scene::AddMaterial(const Material& material)
{
  materials_.push_back(material);
}

void Scene::AddObject(std::shared_ptr<Object> object)
{
  objects_.push_back(object);
}
}
}
