#include "softphys/viewer/camera.h"

namespace softphys
{
namespace
{
const double PI = 3.1415926535897932384626433832795;

constexpr double DegreeToRadian(double degree)
{
  return degree / 180. * PI;
}
}

Camera::Camera()
  : Camera(Type::Orthogonal)
{
}

Camera::Camera(Type type)
  : type_(type),
  eye_(0., -1., 1.), up_(0., 0., 1.), direction_(0., 1., 0.), zoom_(1.),
  near_(0.1), far_(100.),
  fovy_(DegreeToRadian(60.)), aspect_(4. / 3.),
  translate_sensitivity_(0.001, 0.001),
  rotate_sensitivity_(0.001, 0.001),
  zoom_sensitivity_(0.001)
{
}

void Camera::Translate(double x, double y)
{
  Eigen::Vector3d vz = -direction_;
  Eigen::Vector3d vx = up_.cross(vz).normalized();
  Eigen::Vector3d vy = vz.cross(vx);

  eye_ += - vx * x * translate_sensitivity_.first + vy * y * translate_sensitivity_.second;
}

void Camera::Rotate(double x, double y)
{
  Eigen::Vector3d vz = -direction_;
  Eigen::Vector3d vx = up_.cross(vz).normalized();
  Eigen::Vector3d vy = vz.cross(vx);

  Eigen::Matrix3d m;
  m.col(0) = vx;
  m.col(1) = vy;
  m.col(2) = vz;

  direction_ = (Eigen::AngleAxisd(-x * rotate_sensitivity_.first, up_) * 
    Eigen::AngleAxisd(-y * rotate_sensitivity_.second, vx) * direction_).normalized();
}

void Camera::Zoom(double x, double y)
{
  double prev_zoom = zoom_;
  zoom_ += y * zoom_sensitivity_;
  if (zoom_ < minimum_zoom_)
    zoom_ = minimum_zoom_;
  if (zoom_ > maximum_zoom_)
    zoom_ = maximum_zoom_;

  eye_ -= (zoom_ - prev_zoom) * direction_;
}

Eigen::Matrix4f Camera::Projectionf()
{
  return Projection().cast<float>();
}

Eigen::Matrix4d Camera::Projection()
{
  switch (type_)
  {
  case Type::Orthogonal:
    return Orthogonal();

  case Type::Perspective:
    return Perspective();

  default:
    return Perspective();
  }
}

Eigen::Matrix4f Camera::Perspectivef()
{
  return Perspective().cast<float>();
}

Eigen::Matrix4d Camera::Perspective()
{
  Eigen::Matrix4d m;

  m.setZero();
  m(1, 1) = 1. / std::tan(fovy_ / 2.);
  m(0, 0) = m(1, 1) / aspect_;
  m(2, 2) = -(far_ + near_) / (far_ - near_);
  m(2, 3) = -2. * far_ * near_ / (far_ - near_);
  m(3, 2) = -1.;

  return m;
}

Eigen::Matrix4f Camera::Orthogonalf()
{
  return Orthogonal().cast<float>();
}

Eigen::Matrix4d Camera::Orthogonal()
{
  Eigen::Matrix4d m;

  m.setZero();
  m(1, 1) = 1. / zoom_;
  m(0, 0) = m(1, 1) / aspect_;
  m(2, 2) = -2. / (far_ - near_);
  m(2, 3) = - (far_ + near_) / (far_ - near_);
  m(3, 3) = 1.;

  return m;
}

Eigen::Matrix4f Camera::Viewf()
{
  return View().cast<float>();
}

Eigen::Matrix4d Camera::View()
{
  Eigen::Vector3d z = -direction_;
  Eigen::Vector3d x = up_.cross(z).normalized();
  Eigen::Vector3d y = z.cross(x);

  Eigen::Matrix4d m;

  m(0, 0) = x(0);
  m(1, 0) = y(0);
  m(2, 0) = z(0);
  m(3, 0) = 0.;
  m(0, 1) = x(1);
  m(1, 1) = y(1);
  m(2, 1) = z(1);
  m(3, 1) = 0.;
  m(0, 2) = x(2);
  m(1, 2) = y(2);
  m(2, 2) = z(2);
  m(3, 2) = 0.;
  m(0, 3) = 0.;
  m(1, 3) = 0.;
  m(2, 3) = 0.;
  m(3, 3) = 1.;

  Eigen::Matrix4d t;
  t.setIdentity();
  t.block(0, 3, 3, 1) = -eye_;

  return m * t;
}

Eigen::Matrix4f Camera::CameraTransformf()
{
  Eigen::Vector3f z = -direction_.normalized().cast<float>();
  Eigen::Vector3f x = up_.cast<float>().cross(z).normalized();
  Eigen::Vector3f y = z.cross(x);

  Eigen::Matrix4f m;

  m(0, 0) = x(0);
  m(1, 0) = x(1);
  m(2, 0) = x(2);
  m(3, 0) = 0.f;
  m(0, 1) = y(0);
  m(1, 1) = y(1);
  m(2, 1) = y(2);
  m(3, 1) = 0.f;
  m(0, 2) = z(0);
  m(1, 2) = z(1);
  m(2, 2) = z(2);
  m(3, 2) = 0.f;
  m(0, 3) = eye_(0);
  m(1, 3) = eye_(1);
  m(2, 3) = eye_(2);
  m(3, 3) = 1.f;

  return m;

}

std::vector<Eigen::Vector3d> Camera::FrustrumVertices()
{
  std::vector<Eigen::Vector3d> vertices;

  Eigen::Matrix4d vinv = View().inverse();

  double t;
  double r;
  double f;

  switch (type_)
  {
  case Type::Perspective:
    t = std::tan(fovy_ / 2.) * near_;
    r = t * aspect_;
    f = far_ / near_;
    vertices.push_back((vinv * Eigen::Vector4d(-r, -t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, -t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r, t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r * f, -t * f, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r * f, -t * f, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r * f, t * f, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r * f, t * f, -far_, 1.)).block(0, 0, 3, 1));
    break;

  case Type::Orthogonal:
    t = zoom_;
    r = zoom_ * aspect_;
    vertices.push_back((vinv * Eigen::Vector4d(-r, -t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, -t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r, t, -near_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r, -t, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, -t, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(r, t, -far_, 1.)).block(0, 0, 3, 1));
    vertices.push_back((vinv * Eigen::Vector4d(-r, t, -far_, 1.)).block(0, 0, 3, 1));
    break;
  }

  return vertices;
}
}
