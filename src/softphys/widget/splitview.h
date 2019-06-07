#ifndef SOFTPHYS_WIDGET_SPLITVIEW_H_
#define SOFTPHYS_WIDGET_SPLITVIEW_H_

#include "softphys/widget/widget.h"

#include <memory>

namespace softphys
{
namespace widget
{
class Splitview : public Widget
{
public:
  enum class Split
  {
    Horizontal,
    Vertical
  };

public:
  Splitview() = delete;
  Splitview(Painter* painter, Split split, std::shared_ptr<Widget> widget1, std::shared_ptr<Widget> widget2, double partition = 0.5);

  void Keyboard(int key, int action, int mods) override;
  void MouseMove(double x, double y) override;
  void MouseButton(double x, double y, Mouse::Button button, Mouse::Status action, int mods) override;

  void Resize(double width, double height) override;

  void Draw() override;

  void SetPartition(double partition);

private:
  void UpdateChildrenWidgetSize();

  Split split_;
  double partition_;
  std::shared_ptr<Widget> widget1_;
  std::shared_ptr<Widget> widget2_;

  int mouse_dragging_widget_ = -1;
};
}
}

#endif // SOFTPHYS_WIDGET_SPLITVIEW_H_
