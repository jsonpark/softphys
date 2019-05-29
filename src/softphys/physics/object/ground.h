#ifndef SOFTPHYS_PHYSICS_OBJECT_GROUND_H_
#define SOFTPHYS_PHYSICS_OBJECT_GROUND_H_

#include "softphys/physics/object/object.h"

namespace softphys
{
class Ground : public Object
{
public:
  Ground() = delete;
  Ground(const Eigen::Vector3d& normal, const Eigen::Vector3d& center);
  ~Ground();

private:
  Eigen::Vector3d normal_;
  Eigen::Vector3d center_;
};
}

#endif // SOFTPHYS_PHYSICS_OBJECT_GROUND_H_