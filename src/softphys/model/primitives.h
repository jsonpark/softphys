#ifndef SOFTPHYS_MODEL_PRIMITIVES_H_
#define SOFTPHYS_MODEL_PRIMITIVES_H_

#include "softphys/model/model.h"

#include "softphys/model/primitive/primitive.h"
#include "softphys/data/eigen.h"

namespace softphys
{
namespace model
{
class Primitives : public Model
{
public:
  Primitives() = delete;
  Primitives(const std::string& name);
  virtual ~Primitives();
  
  bool IsPrimitives() const noexcept override
  {
    return true;
  }

  void AddPrimitive(const Affine3d& trasnform, std::shared_ptr<Primitive> primitive);

  auto NumPrimitives() const
  {
    return primitives_.size();
  }

  auto GetPrimitive(int i) const
  {
    return primitives_[i];
  }

  const auto& GetTransform(int i) const
  {
    return transforms_[i];
  }

private:
  std::vector<std::shared_ptr<Primitive>> primitives_;
  std::vector<Affine3d> transforms_;
};
}
}

#endif // SOFTPHYS_MODEL_PRIMITIVES_H_
