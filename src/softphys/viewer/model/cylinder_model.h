#ifndef SOFTPHYS_VIEWER_MODEL_CYLINDER_MODEL_H_
#define SOFTPHYS_VIEWER_MODEL_CYLINDER_MODEL_H_

#include "softphys/viewer/model/model.h"

#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_vertex_array.h"

#include <Eigen/Dense>

namespace softphys
{
namespace viewer
{
class CylinderModel : public Model
{
public:
  CylinderModel() = delete;
  CylinderModel(int subdivision_level);

  ~CylinderModel() = default;

  void Draw() override;

private:
  template<typename T, typename... Ts>
  void PushToBuffer(T v, Ts... args)
  {
    buffer_.push_back(static_cast<float>(v));
    PushToBuffer(args...);
  }

  template<>
  void PushToBuffer(float v)
  {
    buffer_.push_back(static_cast<float>(v));
  }

  int subdivision_level_;

  std::vector<float> buffer_;
  std::vector<unsigned int> indices_;

  GlVertexArray vao_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> vbo_;
  GlBuffer<unsigned int, GlBufferTarget::ElementArrayBuffer, GlBufferUsage::StaticDraw> ibo_;
};
}
}

#endif // SOFTPHYS_VIEWER_MODEL_CYLINDER_MODEL_H_
