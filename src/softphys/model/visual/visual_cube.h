#ifndef SOFTPHYS_MODEL_VISUAL_VISUAL_CUBE_H_
#define SOFTPHYS_MODEL_VISUAL_VISUAL_CUBE_H_

#include "softphys/model/visual/visual.h"

#include "softphys/data/eigen.h"

namespace softphys
{
namespace model
{
class VisualCube : public Visual
{
public:
  VisualCube() = delete;
  VisualCube(const std::string& material_name, const Vector3f& size);
  ~VisualCube();

  bool IsCube() const noexcept override
  {
    return true;
  }

  void SetSize(const Vector3f& size)
  {
    size_ = size;
  }

  const auto& Size() const
  {
    return size_;
  }

private:
  Vector3f size_;
};
}
}

#endif // SOFTPHYS_MODEL_VISUAL_VISUAL_CUBE_H_
