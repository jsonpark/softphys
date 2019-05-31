#ifndef SOFTPHYS_VIEWER_MATERIAL_H_
#define SOFTPHYS_VIEWER_MATERIAL_H_

#include <Eigen/Dense>

namespace softphys
{
struct Material
{
  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  float shininess;
};
}

#endif // SOFTPHYS_VIEWER_MATERIAL_H_
