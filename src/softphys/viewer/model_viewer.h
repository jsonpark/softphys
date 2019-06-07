#ifndef SOFTPHYS_VIEWER_MODEL_VIEWER_H_
#define SOFTPHYS_VIEWER_MODEL_VIEWER_H_

#include "softphys/viewer/window.h"

#include "softphys/viewer/shader/gl_program.h"
#include "softphys/viewer/model/ground_model.h"
#include "softphys/scene/scene.h"

namespace softphys
{
class ModelViewer : public Window
{
  friend class Engine;

public:
  ModelViewer() = delete;
  ModelViewer(Engine* engine, int x, int y, int width, int height);
  ~ModelViewer();

  ModelViewer(const ModelViewer& rhs) = delete;
  ModelViewer& operator = (const ModelViewer& rhs) = delete;

  ModelViewer(ModelViewer&& rhs) = default;
  ModelViewer& operator = (ModelViewer&& rhs) = default;

  void Resize(int width, int height) override;
  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(int button, int action, int mods) override;

  void Initialize() override;
  void Display() override;

  void LoadScene(const std::string& filename);

private:
  Camera camera_;
  Mouse mouse_;

  // Shaders
  GlProgram ground_program_;
  GlProgram light_program_;

  // Scene
  std::shared_ptr<scene::Scene> scene_;
  std::unique_ptr<viewer::GroundModel> ground_model_;
};
}

#endif // SOFTPHYS_VIEWER_MODEL_VIEWER_H_
