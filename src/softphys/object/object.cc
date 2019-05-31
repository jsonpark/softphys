#include "softphys/object/object.h"

namespace softphys
{
Object::Object()
  : transform_(Eigen::Affine3d::Identity())
{
  material_.ambient_ = Eigen::Vector4f(0.2f, 0.2f, 0.2f, 1.f);
  material_.diffuse_ = Eigen::Vector4f(0.8f, 0.2f, 0.2f, 1.f);
  material_.specular_ = Eigen::Vector4f(0.2f, 0.2f, 0.2f, 1.f);
}

Object::~Object() = default;
}
