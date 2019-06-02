#include "softphys/model/modelset.h"

namespace softphys
{
namespace model
{
Modelset::Modelset() = default;

Modelset::~Modelset() = default;

void Modelset::AddMaterial(std::shared_ptr<Material> material)
{
  materials_[material->Name()] = material;
}

void Modelset::AddModel(std::shared_ptr<Model> model)
{
  models_[model->Name()] = model;
}

std::shared_ptr<Material> Modelset::GetMaterial(const std::string& key) const
{
  auto it = materials_.find(key);
  if (it != materials_.cend())
    return it->second;

  return nullptr;
}

std::shared_ptr<Model> Modelset::GetModel(const std::string& key) const
{
  auto it = models_.find(key);
  if (it != models_.cend())
    return it->second;

  return nullptr;
}
}
}
