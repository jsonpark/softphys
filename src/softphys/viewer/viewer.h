#ifndef SOFTPHYS_VIEWER_VIEWER_H_
#define SOFTPHYS_VIEWER_VIEWER_H_

#include "softphys/viewer/window.h"

#include "softphys/data/texture.h"
#include "softphys/viewer/gl_texture.h"
#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_program.h"
#include "softphys/viewer/gl_shader.h"
#include "softphys/viewer/gl_vertex_array.h"
#include "softphys/font/font_face.h"
#include "softphys/font/gl_glyphs.h"
#include "softphys/physics/physics.h"
#include "softphys/viewer/model/sphere_model.h"
#include "softphys/viewer/model/ground_model.h"
#include "softphys/scene/scene.h"
#include "softphys/model/modelset.h"

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

  void DisplayPhysicsScene(std::unique_ptr<Physics> physics);

  void Resize(int width, int height) override;
  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(int button, int action, int mods) override;

  void Initialize() override;
  void Display() override;

  auto GetScene()
  {
    return scene_;
  }

  void LoadModels(const std::string& filename);
  void LoadScene(const std::string& filename);
  void LoadPhysics(const std::string& filename);

private:
  Camera camera_;
  Mouse mouse_;

  // Shaders
  GlProgram texture_program_;
  GlProgram uniform_color_program_;
  GlProgram ground_program_;
  GlProgram light_program_;

  // Font
  void RenderText(const std::wstring& s, float x, float y, float font_size, Eigen::Vector3f color);
  GlProgram text_program_;
  GlGlyphs glyphs_;
  GlVertexArray glyph_array_;
  GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw> glyph_buffer_;

  // Models
  std::shared_ptr<model::Modelset> modelset_;

  // Physics
  bool animation_ = false;
  double timestamp_ = 0.;
  std::shared_ptr<Physics> physics_;

  std::unique_ptr<viewer::SphereModel> sphere_model_;
  std::unique_ptr<viewer::GroundModel> ground_model_;

  // Scene
  std::shared_ptr<scene::Scene> scene_;
};
}

#endif // SOFTPHYS_VIEWER_VIEWER_H_
