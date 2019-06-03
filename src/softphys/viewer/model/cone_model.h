#ifndef SOFTPHYS_VIEWER_MODEL_CONE_MODEL_H_
#define SOFTPHYS_VIEWER_MODEL_CONE_MODEL_H_

#include "softphys/viewer/model/model.h"

#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_vertex_array.h"

#include <Eigen/Dense>

namespace softphys
{
namespace viewer
{
class ConeModel : public Model
{
public:
  ConeModel() = delete;
  ConeModel(int subdivision_level);

  ~ConeModel() = default;

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

#endif // SOFTPHYS_VIEWER_MODEL_CONE_MODEL_H_
