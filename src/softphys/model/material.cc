#include "softphys/model/material.h"

namespace softphys
{
namespace model
{
Material::Material(const std::string& name)
  : name_(name)
{
}

Material::Material(const std::string& name, const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess)
  : name_(name),
  ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess)
{
}

Material::~Material() = default;

void Material::Set(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess)
{
  ambient_ = ambient;
  diffuse_ = diffuse;
  specular_ = specular;
  shininess_ = shininess;
}
}
}
