#ifndef SOFTPHYS_MODEL_VISUAL_VISUAL_SPHERE_H_
#define SOFTPHYS_MODEL_VISUAL_VISUAL_SPHERE_H_

#include "softphys/model/visual/visual.h"

namespace softphys
{
namespace model
{
class VisualSphere : public Visual
{
public:
  VisualSphere() = delete;
  VisualSphere(const std::string& material_name, double radius);
  ~VisualSphere();

  bool IsSphere() const noexcept override
  {
    return true;
  }

  void SetRadius(double radius)
  {
    radius_ = radius;
  }

  auto Radius() const
  {
    return radius_;
  }

private:
  double radius_;
};
}
}

#endif // SOFTPHYS_MODEL_VISUAL_VISUAL_SPHERE_H_
