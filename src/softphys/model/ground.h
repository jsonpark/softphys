#ifndef SOFTPHYS_MODEL_GROUND_H_
#define SOFTPHYS_MODEL_GROUND_H_

#include <string>

#include "softphys/model/model.h"

namespace softphys
{
namespace model
{
class Ground : public Model
{
public:
  Ground() = delete;
  Ground(const std::string& name);
  ~Ground();

  bool IsGround() const noexcept override
  {
    return true;
  }

  void SetMaterialName(const std::string& name)
  {
    material_name_ = name;
  }

  const auto& MaterialName()
  {
    return material_name_;
  }

private:
  std::string material_name_;
};
}
}

#endif // SOFTPHYS_MODEL_GROUND_H_
