#include "softphys/viewer/model/cone_model.h"

namespace softphys
{
namespace viewer
{
namespace
{
const double pi = 3.1415926535897932384626433832795;
}

ConeModel::ConeModel(int subdivision_level)
  : Model(),
  subdivision_level_(subdivision_level)
{
  // Bottom
  PushToBuffer(0.f, 0.f, 0.f);
  PushToBuffer(0.f, 0.f, -1.f);
  PushToBuffer(0.5f, 0.5f);

  for (int i = 0; i < subdivision_level_; i++)
  {
    const auto t = static_cast<float>(i) / subdivision_level_;
    auto theta = static_cast<float>(pi) * 2.f * t;
    auto c = std::cos(theta);
    auto s = std::sin(theta);

    PushToBuffer(c, s, 0.f);
    PushToBuffer(0.f, 0.f, -1.f);
    PushToBuffer(c, s);
  }

  indices_.push_back(0);
  for (int i = subdivision_level_; i > 0; i -- )
    indices_.push_back(i);
  indices_.push_back(subdivision_level_);

  // Side
  static const float sqrt2 = std::sqrt(2.f);
  for (int i = 0; i < subdivision_level_; i++)
  {
    const auto t = static_cast<float>(i) / subdivision_level_;
    auto theta = static_cast<float>(pi) * 2.f * t;
    auto c = std::cos(theta);
    auto s = std::sin(theta);

    PushToBuffer(c, s, 0.f);
    PushToBuffer(c * sqrt2, s * sqrt2, sqrt2);
    PushToBuffer(t, 0.f);

    PushToBuffer(0.f, 0.f, 1.f);
    PushToBuffer(c * sqrt2, s * sqrt2, sqrt2);
    PushToBuffer(t, 1.f);
  }

  const int base = subdivision_level_ + 1;
  for (int i = 0; i < subdivision_level_; i++)
  {
    indices_.push_back(base + i * 2 + 1);
    indices_.push_back(base + i * 2);
  }
  indices_.push_back(base);
  indices_.push_back(base + 1);

  vbo_ = decltype(vbo_)(buffer_);
  ibo_ = decltype(ibo_)(indices_);

  vao_.VertexAttribPointer(0, 3, vbo_, 8, 0);
  vao_.VertexAttribPointer(1, 3, vbo_, 8, 3);
  vao_.VertexAttribPointer(2, 2, vbo_, 8, 6);
}

void ConeModel::Draw()
{
  vao_.DrawElements(GlVertexArray::DrawType::TriangleFan, ibo_, subdivision_level_ + 2, 0);
  vao_.DrawElements(GlVertexArray::DrawType::TriangleStrip, ibo_, subdivision_level_ * 2 + 2, subdivision_level_ + 2);
}
}
}
