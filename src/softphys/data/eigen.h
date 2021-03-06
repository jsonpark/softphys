#ifndef SOFTPHYS_DATA_EIGEN_H_
#define SOFTPHYS_DATA_EIGEN_H_

#include <Eigen/Dense>

namespace softphys
{
// Fixed-size data
using Vector2f = Eigen::Matrix<float, 2, 1, Eigen::DontAlign>;
using Vector2d = Eigen::Matrix<double, 2, 1, Eigen::DontAlign>;
using Vector3f = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
using Vector3d = Eigen::Matrix<double, 3, 1, Eigen::DontAlign>;
using Vector4f = Eigen::Matrix<float, 4, 1, Eigen::DontAlign>;
using Vector4d = Eigen::Matrix<double, 4, 1, Eigen::DontAlign>;
using Affine3f = Eigen::Transform<float, 3, Eigen::DontAlign>;
using Affine3d = Eigen::Transform<double, 3, Eigen::DontAlign>;
using Quaternionf = Eigen::Quaternion<float, Eigen::DontAlign>;
using Quaterniond = Eigen::Quaternion<double, Eigen::DontAlign>;
using Matrix3f = Eigen::Matrix<float, 3, 3, Eigen::DontAlign>;
using Matrix3d = Eigen::Matrix<double, 3, 3, Eigen::DontAlign>;
using Matrix4f = Eigen::Matrix<float, 4, 4, Eigen::DontAlign>;
using Matrix4d = Eigen::Matrix<double, 4, 4, Eigen::DontAlign>;

// Variable size data doesn't have the alignment option
using VectorXf = Eigen::VectorXf;
using VectorXd = Eigen::VectorXd;
using MatrixXf = Eigen::MatrixXf;
using MatrixXd = Eigen::MatrixXd;
}

#endif // SOFTPHYS_DATA_EIGEN_H_
