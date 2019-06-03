#ifndef SOFTPHYS_VIEWER_MODEL_POLAR_SPHERE_MODEL_H_
#define SOFTPHYS_VIEWER_MODEL_POLAR_SPHERE_MODEL_H_

#include "softphys/viewer/model/model.h"

#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_vertex_array.h"
#include "softphys/data/eigen.h"

namespace softphys
{
namespace viewer
{
class PolarSphereModel : public Model
{
public:
  PolarSphereModel() = delete;
  PolarSphereModel(int subdivision_level);

  ~PolarSphereModel() = default;

  void Draw() override;

private:
  void Merge();

  int subdivision_level_;

  std::vector<Vector3f> vertices_;
  std::vector<Vector2f> tex_coords_;
  std::vector<unsigned int> indices_;

  GlVertexArray vao_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> vbo_;
  GlBuffer<unsigned int, GlBufferTarget::ElementArrayBuffer, GlBufferUsage::StaticDraw> ibo_;
};
}
}

#endif // SOFTPHYS_VIEWER_MODEL_POLAR_SPHERE_MODEL_H_
