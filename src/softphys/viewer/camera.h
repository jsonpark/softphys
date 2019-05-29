#ifndef SOFTPHYS_VIEWER_CAMERA_H_
#define SOFTPHYS_VIEWER_CAMERA_H_

#include <vector>

#include <Eigen/Dense>

namespace softphys
{
class Camera
{
public:
  enum class Type
  {
    Orthogonal,
    Perspective,
  };

public:
  Camera();
  explicit Camera(Type type);

  void SetEye(const Eigen::Vector3d& eye)
  {
    eye_ = eye;
  }

  void SetDirection(const Eigen::Vector3d& direction)
  {
    direction_ = direction;
  }

  void SetUp(const Eigen::Vector3d& up)
  {
    up_ = up;
  }

  void SetNear(double n) noexcept
  {
    near_ = n;
  }

  void SetFar(double f) noexcept
  {
    far_ = f;
  }

  void SetZoom(double zoom) noexcept
  {
    zoom_ = zoom;
  }

  void SetAspect(int width, int height) noexcept
  {
    aspect_ = static_cast<double>(width) / height;
  }

  void SetAspect(double aspect) noexcept
  {
    aspect_ = aspect;
  }

  auto GetFovy() const
  {
    return fovy_;
  }

  auto GetAspect() const
  {
    return aspect_;
  }

  auto GetNear() const
  {
    return near_;
  }

  auto GetFar() const
  {
    return far_;
  }

  const auto& GetEye() const
  {
    return eye_;
  }

  void Translate(double x, double y);
  void Rotate(double x, double y);
  void Zoom(double x, double y);

  Eigen::Matrix4f Projectionf();
  Eigen::Matrix4d Projection();

  Eigen::Matrix4f Perspectivef();
  Eigen::Matrix4d Perspective();

  Eigen::Matrix4f Orthogonalf();
  Eigen::Matrix4d Orthogonal();

  Eigen::Matrix4f Viewf();
  Eigen::Matrix4d View();

  Eigen::Matrix4f CameraTransformf();

  std::vector<Eigen::Vector3d> FrustrumVertices();

private:
  static constexpr double minimum_zoom_ = 0.001;
  static constexpr double maximum_zoom_ = 10.;

  Type type_;

  Eigen::Vector3d eye_;
  Eigen::Vector3d direction_;
  Eigen::Vector3d up_;
  double zoom_;

  double near_;
  double far_;
  double aspect_;
  double fovy_;

  std::pair<double, double> translate_sensitivity_;
  std::pair<double, double> rotate_sensitivity_;
  double zoom_sensitivity_;
};
}

#endif // SOFTPHYS_VIEWER_CAMERA_H_
