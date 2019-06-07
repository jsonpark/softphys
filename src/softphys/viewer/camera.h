#ifndef SOFTPHYS_VIEWER_CAMERA_H_
#define SOFTPHYS_VIEWER_CAMERA_H_

#include <vector>

#include "softphys/data/eigen.h"

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

  Matrix4f Projectionf() const;
  Matrix4d Projection() const;

  Matrix4f Perspectivef() const;
  Matrix4d Perspective() const;

  Matrix4f Orthogonalf() const;
  Matrix4d Orthogonal() const;

  Matrix4f Viewf() const;
  Matrix4d View() const;

  Matrix4f CameraTransformf() const;

  std::vector<Vector3d> FrustrumVertices();

private:
  static constexpr double minimum_zoom_ = 0.001;
  static constexpr double maximum_zoom_ = 10.;

  Type type_;

  Vector3d eye_;
  Vector3d direction_;
  Vector3d up_;
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
