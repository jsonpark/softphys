#include "softphys/viewer/model/sphere_model.h"

namespace softphys
{
SphereModel::SphereModel(int subdivision_level)
  : subdivision_level_(subdivision_level)
{
  Generate(Eigen::Vector3d(1., 0., 0.), Eigen::Vector3d(0., 1., 0.), Eigen::Vector3d(0., 0., 1.));
  Generate(Eigen::Vector3d(0., 1., 0.), Eigen::Vector3d(-1., 0., 0.), Eigen::Vector3d(0., 0., 1.));
  Generate(Eigen::Vector3d(-1., 0., 0.), Eigen::Vector3d(0., -1., 0.), Eigen::Vector3d(0., 0., 1.));
  Generate(Eigen::Vector3d(0., -1., 0.), Eigen::Vector3d(1., 0., 0.), Eigen::Vector3d(0., 0., 1.));
  Generate(Eigen::Vector3d(1., 0., 0.), Eigen::Vector3d(0., -1., 0.), Eigen::Vector3d(0., 0., -1.));
  Generate(Eigen::Vector3d(0., -1., 0.), Eigen::Vector3d(-1., 0., 0.), Eigen::Vector3d(0., 0., -1.));
  Generate(Eigen::Vector3d(-1., 0., 0.), Eigen::Vector3d(0., 1., 0.), Eigen::Vector3d(0., 0., -1.));
  Generate(Eigen::Vector3d(0., 1., 0.), Eigen::Vector3d(1., 0., 0.), Eigen::Vector3d(0., 0., -1.));
  Merge();

  std::vector<float> vertices_unpacked(vertices_.size() * 3);
  for (int i = 0; i < vertices_.size(); i++)
  {
    vertices_unpacked[3 * i] = vertices_[i](0);
    vertices_unpacked[3 * i + 1] = vertices_[i](1);
    vertices_unpacked[3 * i + 2] = vertices_[i](2);
  }
  vbo_ = decltype(vbo_)(vertices_unpacked);
  ibo_ = decltype(ibo_)(indices_);

  vao_.VertexAttribPointer(0, 3, vbo_);
  vao_.VertexAttribPointer(1, 3, vbo_);
}

SphereModel::~SphereModel() = default;

void SphereModel::Draw()
{
  vao_.DrawElements(GlVertexArray::DrawType::Triangles, ibo_);
}

void SphereModel::Generate(Eigen::Vector3d p0, Eigen::Vector3d p1, Eigen::Vector3d p2, int level)
{
  if (level == subdivision_level_)
  {
    auto idx = vertices_.size();
    vertices_.push_back(p0);
    vertices_.push_back(p1);
    vertices_.push_back(p2);
    indices_.push_back(idx);
    indices_.push_back(idx + 1);
    indices_.push_back(idx + 2);
    return;
  }

  Eigen::Vector3d m01 = ((p0 + p1) / 2.).normalized();
  Eigen::Vector3d m12 = ((p1 + p2) / 2.).normalized();
  Eigen::Vector3d m20 = ((p2 + p0) / 2.).normalized();

  Generate(p0, m01, m20, level + 1);
  Generate(p1, m12, m01, level + 1);
  Generate(p2, m20, m12, level + 1);
  Generate(m01, m12, m20, level + 1);
}

void SphereModel::Merge()
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

  for (int i=0; i<indices_.size(); i++)
    indices_[i] = index_map[indices_[i]];
}
}
