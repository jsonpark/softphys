#ifndef SOFTPHYS_MODEL_MODEL_H_
#define SOFTPHYS_MODEL_MODEL_H_

#include <vector>
#include <unordered_map>
#include <memory>

namespace softphys
{
namespace model
{
class Model
{
public:
  Model() = delete;
  Model(const std::string& name);
  virtual ~Model();

  virtual bool IsGround() const noexcept
  {
    return false;
  }

  virtual bool IsPrimitives() const noexcept
  {
    return false;
  }

  const auto& Name() const
  {
    return name_;
  }

private:
  std::string name_;
  std::string material_name_;
};
}
}

#endif // SOFTPHYS_MODEL_MODEL_H_
