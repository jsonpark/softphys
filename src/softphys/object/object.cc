#include "softphys/object/object.h"

namespace softphys
{
Object::Object()
  : transform_(Eigen::Affine3d::Identity())
{
  material_.ambient = Eigen::Vector3f(0.2f, 0.2f, 0.2f);
  material_.diffuse = Eigen::Vector3f(0.8f, 0.2f, 0.2f);
  material_.specular = Eigen::Vector3f(0.2f, 0.2f, 0.2f);
}

Object::~Object() = default;
}
