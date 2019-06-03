#ifndef SOFTPHYS_VIEWER_MODEL_GROUND_MODEL_H_
#define SOFTPHYS_VIEWER_MODEL_GROUND_MODEL_H_

#include "softphys/viewer/model/model.h"

#include "softphys/viewer/gl_texture_2d.h"
#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_vertex_array.h"

#include <Eigen/Dense>

namespace softphys
{
namespace viewer
{
class GroundModel : public Model
{
public:
  GroundModel();

  ~GroundModel();

  void Draw() override;

private:
  void GenerateTexture(int size);

  int subdivision_level_;

  GlTexture2D texture_;
  GlVertexArray vao_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> vbo_;
};
}
}

#endif // SOFTPHYS_VIEWER_MODEL_GROUND_MODEL_H_
