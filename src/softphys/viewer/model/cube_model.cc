#include "softphys/viewer/model/cube_model.h"

namespace softphys
{
namespace viewer
{
CubeModel::CubeModel()
  : Model()
{
  int base = 0;

  PushToBuffer(1.f, -1.f, -1.f, 1.f, 0.f, 0.f, 0.f, 0.f);
  PushToBuffer(1.f,  1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f);
  PushToBuffer(1.f, -1.f,  1.f, 1.f, 0.f, 0.f, 0.f, 1.f);
  PushToBuffer(1.f,  1.f,  1.f, 1.f, 0.f, 0.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  PushToBuffer(-1.f, -1.f, -1.f, -1.f, 0.f, 0.f, 0.f, 0.f);
  PushToBuffer(-1.f, -1.f,  1.f, -1.f, 0.f, 0.f, 0.f, 1.f);
  PushToBuffer(-1.f,  1.f, -1.f, -1.f, 0.f, 0.f, 1.f, 0.f);
  PushToBuffer(-1.f,  1.f,  1.f, -1.f, 0.f, 0.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  PushToBuffer(-1.f, 1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f);
  PushToBuffer(-1.f, 1.f,  1.f, 0.f, 1.f, 0.f, 0.f, 1.f);
  PushToBuffer( 1.f, 1.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f);
  PushToBuffer( 1.f, 1.f,  1.f, 0.f, 1.f, 0.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  PushToBuffer(-1.f, -1.f, -1.f, 0.f, -1.f, 0.f, 0.f, 0.f);
  PushToBuffer( 1.f, -1.f, -1.f, 0.f, -1.f, 0.f, 1.f, 0.f);
  PushToBuffer(-1.f, -1.f,  1.f, 0.f, -1.f, 0.f, 0.f, 1.f);
  PushToBuffer( 1.f, -1.f,  1.f, 0.f, -1.f, 0.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  PushToBuffer(-1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f);
  PushToBuffer( 1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f);
  PushToBuffer(-1.f,  1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f);
  PushToBuffer( 1.f,  1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  PushToBuffer(-1.f, -1.f, -1.f, 0.f, 0.f, -1.f, 0.f, 0.f);
  PushToBuffer(-1.f,  1.f, -1.f, 0.f, 0.f, -1.f, 0.f, 1.f);
  PushToBuffer( 1.f, -1.f, -1.f, 0.f, 0.f, -1.f, 1.f, 0.f);
  PushToBuffer( 1.f,  1.f, -1.f, 0.f, 0.f, -1.f, 1.f, 1.f);
  indices_.push_back(base);
  indices_.push_back(base + 1);
  indices_.push_back(base + 2);
  indices_.push_back(base + 3);
  indices_.push_back(UINT32_MAX);
  base += 4;

  vbo_ = decltype(vbo_)(buffer_);
  ibo_ = decltype(ibo_)(indices_);

  vao_.VertexAttribPointer(0, 3, vbo_, 8, 0);
  vao_.VertexAttribPointer(1, 3, vbo_, 8, 3);
  vao_.VertexAttribPointer(2, 3, vbo_, 8, 6);
}

void CubeModel::Draw()
{
  vao_.DrawElements(GlVertexArray::DrawType::TriangleStrip, ibo_);
}
}
}
