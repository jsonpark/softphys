#ifndef SOFTPHYS_VIEWER_PAINTER_H_
#define SOFTPHYS_VIEWER_PAINTER_H_

#include "softphys/viewer/window.h"

#include "softphys/widget/viewer.h"
#include "softphys/widget/splitview.h"
#include "softphys/widget/treeview.h"

namespace softphys
{
class Painter : public Window
{
public:
  Painter() = delete;
  Painter(Engine* engine, int x, int y, int width, int height);
  Painter(Engine* engine, const std::string& title, int x, int y, int width, int height);
  ~Painter();

  Painter(const Painter& rhs) = delete;
  Painter& operator = (const Painter& rhs) = delete;

  Painter(Painter&& rhs) = default;
  Painter& operator = (Painter&& rhs) = default;

  void Resize(int width, int height) override;
  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(Mouse::Button button, Mouse::Status action, int mods) override;

  void Initialize() override;
  void Display() override;

  void LoadScene(const std::string& filename);

  void SetViewport();
  void SetViewport(int x, int y, int width, int height);

  void RenderText(const std::wstring& s, float x, float y, float font_size, const Vector3f& color);
  void DrawRect(float xmin, float ymin, float xmax, float ymax, const Vector4f& color);

  const auto& GetMouse() const
  {
    return mouse_;
  }

private:
  Mouse mouse_;

  std::shared_ptr<widget::Splitview> splitview_;
  std::shared_ptr<widget::Treeview> treeview_;
  std::shared_ptr<widget::Viewer> viewer_;

  // Font
  GlProgram text_program_;
  GlGlyphs glyphs_;
  GlVertexArray glyph_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw> glyph_buffer_;

  // Ui
  GlProgram ui_program_;
  GlVertexArray ui_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw> ui_buffer_;
};
}

#endif // SOFTPHYS_VIEWER_VIEWER_H_
