#include "softphys/shape/plane.h"

namespace softphys
{
Plane::Plane() = default;

Plane::Plane(const Eigen::Vector4d& equation)
{
  // Normalize the normal vector
  equation_ = equation / std::sqrt(equation(0) * equation(0) + equation(1) * equation(1) + equation(2) * equation(2));
}

Plane::~Plane() = default;

Eigen::Vector3d Plane::Normal()
{
  return equation_.block(0, 0, 3, 1);
}
}
