#ifndef SOFTPHYS_VIEWER_VIEWER_H_
#define SOFTPHYS_VIEWER_VIEWER_H_

#include "softphys/viewer/window.h"

#include "softphys/widget/viewer.h"
#include "softphys/widget/splitview.h"
#include "softphys/widget/treeview.h"

namespace softphys
{
class ViewerWindow : public Window
{
  friend class Engine;

public:
  ViewerWindow() = delete;
  ViewerWindow(Engine* engine, int x, int y, int width, int height);
  ViewerWindow(Engine* engine, const std::string& title, int x, int y, int width, int height);
  ~ViewerWindow();

  ViewerWindow(const ViewerWindow& rhs) = delete;
  ViewerWindow& operator = (const ViewerWindow& rhs) = delete;

  ViewerWindow(ViewerWindow&& rhs) = default;
  ViewerWindow& operator = (ViewerWindow&& rhs) = default;

  void Resize(int width, int height) override;
  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(int button, int action, int mods) override;

  void Initialize() override;
  void Display() override;

  void LoadScene(const std::string& filename);

private:
  std::shared_ptr<widget::Splitview> splitview_;
  std::shared_ptr<widget::Treeview> treeview_;
  std::shared_ptr<widget::Viewer> viewer_;
};
}

#endif // SOFTPHYS_VIEWER_VIEWER_H_
