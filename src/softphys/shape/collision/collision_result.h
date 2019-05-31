#ifndef SOFTPHYS_SHAPE_COLLISION_COLLISION_RESULT_H_
#define SOFTPHYS_SHAPE_COLLISION_COLLISION_RESULT_H_

#include <Eigen/Dense>

namespace softphys
{
struct CollisionResult
{
  Eigen::Vector3d point; // deepest collision point on the surface of obj1
  Eigen::Vector3d depth; // depth vector from object 1 towards object 2

  //
  // ----------+
  //           |
  //        +--+--------
  //  obj1  |  p  obj2  
  //        +-----------
  //           |
  // ----------+
  //
  //        <--* depth
};
}

#endif // SOFTPHYS_SHAPE_COLLISION_COLLISION_RESULT_H_
