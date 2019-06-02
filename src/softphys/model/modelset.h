#ifndef SOFTPHYS_MODEL_MODELSET_H_
#define SOFTPHYS_MODEL_MODELSET_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "softphys/model/model.h"
#include "softphys/model/material.h"

namespace softphys
{
namespace model
{
class Modelset
{
public:
  Modelset();
  ~Modelset();

  void AddMaterial(std::shared_ptr<Material> material);
  void AddModel(std::shared_ptr<Model> model);

  template<typename... Ts>
  auto CreateMaterial(Ts&& ... args)
  {
    auto material = std::make_shared<Material>(std::forward<Ts>(args)...);
    AddMaterial(material);
    return material;
  }

  template<typename ModelType, typename... Ts>
  auto CreateModel(Ts&& ... args)
  {
    auto model = std::make_shared<ModelType>(std::forward<Ts>(args)...);
    AddModel(model);
    return model;
  }

  std::shared_ptr<Material> GetMaterial(const std::string& key) const;
  std::shared_ptr<Model> GetModel(const std::string& key) const;

private:
  std::unordered_map<std::string, std::shared_ptr<Material>> materials_;
  std::unordered_map<std::string, std::shared_ptr<Model>> models_;
};
}
}

#endif // SOFTPHYS_MODEL_MODELSET_H_
