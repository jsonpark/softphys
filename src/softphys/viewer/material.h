#ifndef SOFTPHYS_VIEWER_MATERIAL_H_
#define SOFTPHYS_VIEWER_MATERIAL_H_

#include <string>

#include <Eigen/Dense>

namespace softphys
{
struct Material
{
  std::string name;
  std::string preset;
  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  float shininess;
};
}

#endif // SOFTPHYS_VIEWER_MATERIAL_H_
