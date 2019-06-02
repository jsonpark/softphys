#include "softphys/viewer/model/ground_model.h"

#include "softphys/data/texture.h"

namespace softphys
{
namespace viewer
{
GroundModel::GroundModel()
  : Model()
{
  GenerateTexture(256);

  std::vector<float> vertex_buffer{
    -100., -100.,
    100., -100.,
    -100., 100.,
    100., 100.
  };

  vbo_ = decltype(vbo_)(vertex_buffer);

  vao_.VertexAttribPointer(0, 2, vbo_);
}

GroundModel::~GroundModel() = default;

void GroundModel::GenerateTexture(int size)
{
  Texture<> texture(size, size);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int color = 127 + ((i < size / 2) ^ (j < size / 2)) * 128;
      texture(i, j, 0) = color;
      texture(i, j, 1) = color;
      texture(i, j, 2) = color;
      texture(i, j, 3) = 255;
    }
  }

  texture_ = decltype(texture_)(texture);
  texture_.Bind();
  texture_.WrapS(GlTextureWrapping::Repeat);
  texture_.WrapT(GlTextureWrapping::Repeat);
  texture_.Unbind();
}

void GroundModel::Draw()
{
  texture_.Bind();
  vao_.DrawArrays(GlVertexArray::DrawType::TriangleStrip, 4);
}
}
}
