#ifndef SOFTPHYS_VIEWER_MATERIAL_H_
#define SOFTPHYS_VIEWER_MATERIAL_H_

#include <Eigen/Dense>

namespace softphys
{
struct Material
{
  Eigen::Vector4f ambient_;
  Eigen::Vector4f diffuse_;
  Eigen::Vector4f specular_;
};
}

#endif // SOFTPHYS_VIEWER_MATERIAL_H_
