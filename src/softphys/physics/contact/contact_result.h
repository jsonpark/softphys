#ifndef SOFTPHYS_PHYSICS_CONTACT_CONTACT_RESULT_H_
#define SOFTPHYS_PHYSICS_CONTACT_CONTACT_RESULT_H_

#include <Eigen/Dense>

namespace softphys
{
enum class ContactType
{
  None,
  PointContact,
  LineContact,
  SurfaceContact,
  Error
};

struct ContactResult
{
  ContactType type = ContactType::None;
  Eigen::Vector3d impulse; // impulse 
  Eigen::Vector3d contact_point; // deepest collision point on the surface of obj1, in world coordinate
  Eigen::Vector3d contact_depth; // depth vector from object 1 towards object 2, in world coordinate

  // Contact without depth
  //
  // ----------+  +-----
  //           | /
  //           |/
  //  obj1     p  obj2
  //           |\
  //           | \
  // ----------+  +-----
  //
  //    ( depth = 0 )
  //
  // Contact with depth
  //
  // ----------+
  //           |
  //        +--+--------
  //  obj1  |  p  obj2
  //        +--+--------
  //           |
  // ----------+
  //
  //        <--* depth
};
}

#endif // SOFTPHYS_PHYSICS_CONTACT_CONTACT_RESULT_H_
