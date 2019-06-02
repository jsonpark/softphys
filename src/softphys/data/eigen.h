#ifndef SOFTPHYS_DATA_EIGEN_H_
#define SOFTPHYS_DATA_EIGEN_H_

#include <Eigen/Dense>

namespace softphys
{
using Vector3f = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
using Vector3d = Eigen::Matrix<double, 3, 1, Eigen::DontAlign>;
using Vector4f = Eigen::Matrix<float, 4, 1, Eigen::DontAlign>;
using Vector4d = Eigen::Matrix<double, 4, 1, Eigen::DontAlign>;
using Affine3f = Eigen::Transform<float, 3, Eigen::DontAlign>;
using Affine3d = Eigen::Transform<double, 3, Eigen::DontAlign>;
using Quaternionf = Eigen::Quaternion<float, Eigen::DontAlign>;
using Quaterniond = Eigen::Quaternion<double, Eigen::DontAlign>;
}

#endif // SOFTPHYS_DATA_EIGEN_H_
