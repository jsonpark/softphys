#ifndef SOFTPHYS_MODEL_VISUAL_VISUAL_H_
#define SOFTPHYS_MODEL_VISUAL_VISUAL_H_

#include <string>

namespace softphys
{
namespace model
{
class Visual
{
public:
  Visual() = delete;
  Visual(const std::string& material_name);
  ~Visual();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual bool IsCube() const noexcept
  {
    return false;
  }

  const auto& MaterialName() const
  {
    return material_name_;
  }

private:
  std::string material_name_;
};
}
}

#endif // SOFTPHYS_MODEL_VISUAL_VISUAL_H_
