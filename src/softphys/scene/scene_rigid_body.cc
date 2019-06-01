#include "softphys/scene/scene_rigid_body.h"

namespace softphys
{
namespace scene
{
RigidBody::RigidBody() = default;

RigidBody::~RigidBody() = default;

void RigidBody::AddPrimitive(std::shared_ptr<Primitive> primitive, const Eigen::Vector3d& position, const Eigen::Quaterniond& orientation)
{
  PrimitiveTransformed p;
  p.primitive = primitive;
  p.transform.setIdentity();
  p.transform.rotate(orientation);
  p.transform.translate(position);

  primitives_.push_back(p);
}
}
}
