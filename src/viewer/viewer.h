#ifndef MODERNGL_VIEWER_H_
#define MODERNGL_VIEWER_H_

#include "softphys/engine/window.h"

#include "softphys/engine/texture.h"
#include "softphys/engine/gl_texture.h"
#include "softphys/engine/gl_buffer.h"
#include "softphys/engine/gl_program.h"
#include "softphys/engine/gl_shader.h"
#include "softphys/engine/gl_vertex_array.h"
#include "softphys/font/font_face.h"
#include "softphys/font/gl_glyphs.h"

namespace softphys
{
class Viewer : public Window
{
  friend class Engine;

public:
  Viewer() = delete;
  Viewer(Engine* engine, int x, int y, int width, int height);
  ~Viewer();

  Viewer(const Viewer& rhs) = delete;
  Viewer& operator = (const Viewer& rhs) = delete;

  Viewer(Viewer&& rhs) = default;
  Viewer& operator = (Viewer&& rhs) = default;

  void Resize(int width, int height) override;
  void MouseMove(double x, double y) override;
  void MouseButton(int button, int action, int mods) override;

  void Initialize() override;
  void Display() override;

private:
  Camera camera_;
  Mouse mouse_;

  // Rectangle viewer
  GlProgram texture_program_;
  GlVertexArray vertex_array_;
  GlVertexArray axis_vertex_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> vertex_buffer_;
  GlBuffer<unsigned int, GlBufferTarget::ElementArrayBuffer, GlBufferUsage::StaticDraw> index_buffer_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw> axis_buffer_;
  GlTexture<GlTextureType::Texture2D> gl_texture1_;
  GlTexture<GlTextureType::Texture2D> gl_texture2_;

  // Font
  void RenderText(const std::wstring& s, float x, float y, float font_size, Eigen::Vector3f color);
  GlProgram text_program_;
  GlGlyphs glyphs_;
  GlVertexArray glyph_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw> glyph_buffer_;
};
}

#endif // MODERNGL_VIEWER_H_
