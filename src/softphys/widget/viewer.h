#ifndef SOFTPHYS_WIDGET_VIEWER_H_
#define SOFTPHYS_WIDGET_VIEWER_H_

#include "softphys/widget/widget.h"

#include "softphys/viewer/shader/gl_program.h"
#include "softphys/viewer/gl_vertex_array.h"
#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/model/polar_sphere_model.h"
#include "softphys/viewer/model/ground_model.h"
#include "softphys/viewer/model/cone_model.h"
#include "softphys/viewer/model/cylinder_model.h"
#include "softphys/viewer/model/cube_model.h"
#include "softphys/viewer/mouse.h"
#include "softphys/scene/scene.h"
#include "softphys/font/gl_glyphs.h"

namespace softphys
{
class Engine;

namespace widget
{
class Viewer : public Widget
{
public:
  Viewer() = delete;
  Viewer(Engine* engine);
  Viewer(Engine* engine, int x, int y, int width, int height);
  ~Viewer();

  Viewer(const Viewer& rhs) = delete;
  Viewer& operator = (const Viewer& rhs) = delete;

  Viewer(Viewer&& rhs) = default;
  Viewer& operator = (Viewer&& rhs) = default;

  void Resize(double width, double height) override;
  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(int button, int action, int mods) override;

  void Initialize() override;
  void Draw() override;

  void LoadScene(const std::string& filename);

private:
  Engine* engine_;

  Camera camera_;
  Mouse mouse_;

  // Shaders
  GlProgram ground_program_;
  GlProgram light_program_;

  // Font
  void RenderText(const std::wstring& s, float x, float y, float font_size, Eigen::Vector3f color);
  GlProgram text_program_;
  GlGlyphs glyphs_;
  GlVertexArray glyph_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw> glyph_buffer_;

  // Models
  void DrawAxis(const Affine3d& transform, double axis_length, double axis_radius);

  // Physics
  bool animation_ = false;
  double timestamp_ = 0.;

  std::unique_ptr<viewer::PolarSphereModel> sphere_model_;
  std::unique_ptr<viewer::CylinderModel> cylinder_model_;
  std::unique_ptr<viewer::ConeModel> cone_model_;
  std::unique_ptr<viewer::CubeModel> cube_model_;
  std::unique_ptr<viewer::GroundModel> ground_model_;

  // Scene
  std::shared_ptr<scene::Scene> scene_;
};
}
}

#endif // SOFTPHYS_WIDGET_VIEWER_H_
