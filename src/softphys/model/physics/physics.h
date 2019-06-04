#ifndef SOFTPHYS_MODEL_PHYSICS_PHYSICS_H_
#define SOFTPHYS_MODEL_PHYSICS_PHYSICS_H_

#include <string>

namespace softphys
{
namespace model
{
class Physics
{
public:
  Physics();
  ~Physics();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

private:
};
}
}

#endif // SOFTPHYS_MODEL_PHYSICS_PHYSICS_H_
