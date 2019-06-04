#ifndef SOFTPHYS_MODEL_MODEL_H_
#define SOFTPHYS_MODEL_MODEL_H_

#include <vector>
#include <unordered_map>
#include <memory>

#include "softphys/model/visual/visual.h"
#include "softphys/model/physics/physics.h"

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

  void SetVisual(std::shared_ptr<Visual> visual)
  {
    visual_ = visual;
  }

  void SetPhysics(std::shared_ptr<Physics> physics)
  {
    physics_ = physics;
  }

  auto GetVisual() const
  {
    return visual_;
  }

  auto GetPhysics() const
  {
    return physics_;
  }

private:
  std::string name_;

  std::shared_ptr<Visual> visual_;
  std::shared_ptr<Physics> physics_;
};
}
}

#endif // SOFTPHYS_MODEL_MODEL_H_
