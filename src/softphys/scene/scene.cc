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
}
}
