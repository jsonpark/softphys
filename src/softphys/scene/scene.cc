#include "softphys/scene/scene.h"

namespace softphys
{
Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::AddLight(const Light& light)
{
  lights_.push_back(light);
}

void Scene::AddMaterial(const std::string& name, const Material& material)
{
  materials_[name] = material;
}
}
