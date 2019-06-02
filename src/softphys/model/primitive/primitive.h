#ifndef SOFTPHYS_MODEL_PRIMITIVE_PRIMITIVE_H_
#define SOFTPHYS_MODEL_PRIMITIVE_PRIMITIVE_H_

#include "softphys/model/model.h"

namespace softphys
{
namespace model
{
class Primitive
{
public:
  Primitive();
  Primitive(const std::string& material_name, double density);
  ~Primitive();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  void SetDensity(double density)
  {
    density_ = density;
  }

  auto Density() const
  {
    return density_;
  }

  void SetMaterialName(const std::string& name)
  {
    material_name_ = name;
  }

  const auto& MaterialName() const
  {
    return material_name_;
  }

private:
  double density_ = 0.;
  std::string material_name_;
};
}
}

#endif // SOFTPHYS_MODEL_PRIMITIVE_PRIMITIVE_H_
