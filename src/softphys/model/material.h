#ifndef SOFTPHYS_MODEL_MATERIAL_H_
#define SOFTPHYS_MODEL_MATERIAL_H_

#include <vector>
#include <unordered_map>
#include <memory>

#include "softphys/data/eigen.h"

namespace softphys
{
namespace model
{
class Material
{
public:
  Material() = delete;
  Material(const std::string& name);
  Material(const std::string& name, const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess);
  virtual ~Material();

  void SetName(const std::string& material_name)
  {
    name_ = material_name;
  }

  const auto& Name() const
  {
    return name_;
  }

  void Set(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess);

  const auto& Ambient() const
  {
    return ambient_;
  }

  const auto& Diffuse() const
  {
    return diffuse_;
  }

  const auto& Specular() const
  {
    return specular_;
  }

  auto Shininess() const
  {
    return shininess_;
  }

private:
  std::string name_;
  Vector3f ambient_{ 0.f, 0.f, 0.f };
  Vector3f diffuse_{ 0.f, 0.f, 0.f };
  Vector3f specular_{ 0.f, 0.f, 0.f };
  float shininess_ = 0.f;
};
}
}

#endif // SOFTPHYS_MODEL_MATERIAL_H_
