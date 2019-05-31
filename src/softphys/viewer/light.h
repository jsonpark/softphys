#ifndef SOFTPHYS_VIEWER_LIGHT_H_
#define SOFTPHYS_VIEWER_LIGHT_H_

#include <Eigen/Dense>

namespace softphys
{
struct Light
{
  enum class Type
  {
    Directional,
    Point
  };

  Type type;

  Eigen::Vector3f position;
  Eigen::Vector3f attenuation;

  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
};
}

#endif // SOFTPHYS_VIEWER_LIGHT_H_
