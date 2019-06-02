#ifndef SOFTPHYS_VIEWER_MODEL_SPHERE_MODEL_H_
#define SOFTPHYS_VIEWER_MODEL_SPHERE_MODEL_H_

#include "softphys/viewer/model/model.h"

#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_vertex_array.h"

#include <Eigen/Dense>

namespace softphys
{
namespace viewer
{
class SphereModel : public Model
{
public:
  SphereModel() = delete;
  SphereModel(int subdivision_level);

  ~SphereModel();

  void Draw() override;

private:
  void Generate(Eigen::Vector3d p0, Eigen::Vector3d p1, Eigen::Vector3d p2, int level = 0);
  void Merge();

  int subdivision_level_;

  std::vector<Eigen::Vector3d> vertices_;
  std::vector<unsigned int> indices_;

  GlVertexArray vao_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> vbo_;
  GlBuffer<unsigned int, GlBufferTarget::ElementArrayBuffer, GlBufferUsage::StaticDraw> ibo_;
};
}
}

#endif // SOFTPHYS_VIEWER_MODEL_SPHERE_MODEL_H_
