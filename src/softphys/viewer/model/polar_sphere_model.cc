#include "softphys/viewer/model/polar_sphere_model.h"

#include <cmath>

namespace softphys
{
namespace viewer
{
namespace
{
static const double pi = 3.1415926535897932384626433832795;
}

PolarSphereModel::PolarSphereModel(int subdivision_level)
  : Model(),
  subdivision_level_(subdivision_level)
{
  // Vertices
  vertices_.emplace_back(0.f, 0.f, -1.f);
  tex_coords_.emplace_back(0.5f, 0.f);

  for (int y = 1; y < subdivision_level_ * 2; y++)
  {
    double u2 = static_cast<double>(y) / (subdivision_level_ * 2.) * 2. - 1.;
    double theta2 = u2 * pi;
    double c2 = std::cos(theta2);
    double s2 = std::sin(theta2);

    for (int x = 0; x < subdivision_level_ * 2; x++)
    {
      double u1 = static_cast<double>(x) / (subdivision_level_ * 2.) * 2. - 1.;
      double theta1 = u1 * pi;
      double c1 = std::cos(theta1);
      double s1 = std::sin(theta1);

      vertices_.emplace_back(c1 * c2, s1 * c2, s2);
      tex_coords_.emplace_back(u1 * c1 + 0.5, s2 + 0.5);
    }
  }

  vertices_.emplace_back(0.f, 0.f, 1.f);
  tex_coords_.emplace_back(0.5f, 1.f);

  // Indices
  int base = 1;
  for (int i = 0; i < subdivision_level_ * 2; i++)
  {
    indices_.push_back(base + i);
    indices_.push_back(0);
  }
  indices_.push_back(base);
  indices_.push_back(0);
  indices_.push_back(UINT32_MAX);
  base += subdivision_level_ * 2;

  for (int y = 2; y < subdivision_level_ * 2; y++)
  {
    for (int x = 0; x < subdivision_level_ * 2; x++)
    {
      indices_.push_back(base + subdivision_level_ * 2 + x);
      indices_.push_back(base + x);
    }
    indices_.push_back(base + subdivision_level_ * 2);
    indices_.push_back(base);
    indices_.push_back(UINT32_MAX);
    base += subdivision_level_ * 2;
  }

  for (int i = 0; i < subdivision_level_ * 2; i++)
  {
    indices_.push_back(vertices_.size() - 1);
    indices_.push_back(base + i);
  }
  indices_.push_back(vertices_.size() - 1);
  indices_.push_back(base);
  indices_.push_back(UINT32_MAX);
  base += subdivision_level_ * 2;

  // To Gl buffer
  std::vector<float> vertices_unpacked(vertices_.size() * 5);
  for (int i = 0; i < vertices_.size(); i++)
  {
    vertices_unpacked[5 * i] = vertices_[i](0);
    vertices_unpacked[5 * i + 1] = vertices_[i](1);
    vertices_unpacked[5 * i + 2] = vertices_[i](2);
    vertices_unpacked[5 * i + 3] = tex_coords_[i](0);
    vertices_unpacked[5 * i + 4] = tex_coords_[i](0);
  }
  vbo_ = decltype(vbo_)(vertices_unpacked);
  ibo_ = decltype(ibo_)(indices_);

  vao_.VertexAttribPointer(0, 3, vbo_, 5, 0);
  vao_.VertexAttribPointer(1, 3, vbo_, 5, 0);
  vao_.VertexAttribPointer(2, 2, vbo_, 5, 3);
}

void PolarSphereModel::Draw()
{
  vao_.DrawElements(GlVertexArray::DrawType::TriangleStrip, ibo_);
}

void PolarSphereModel::Merge()
{
  // TODO: improve from O(n^2) to O(lg n)

  const double threshold = 1e-6;
  const int n = vertices_.size();

  std::vector<int> index_map(n);
  for (int i = 0; i < n; i++)
    index_map[i] = i;

  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = 0; j < i; j++)
    {
      if ((vertices_[i] - vertices_[j]).squaredNorm() <= threshold)
      {
        index_map[i] = j;
        break;
      }
    }
  }

  int counter = 0;
  for (int i = 0; i < n; i++)
  {
    if (index_map[i] == i)
    {
      vertices_[counter] = vertices_[i];
      index_map[i] = counter;
      counter++;
    }
    else
      index_map[i] = index_map[index_map[i]];
  }

  vertices_.resize(counter);

  //for (auto& index : indices_)
    //index = index_map[index];

  for (int i = 0; i < indices_.size(); i++)
    indices_[i] = index_map[indices_[i]];
}
}
}
