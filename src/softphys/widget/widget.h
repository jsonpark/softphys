#ifndef SOFTPHYS_WIDGET_WIDGET_H_
#define SOFTPHYS_WIDGET_WIDGET_H_

#include "softphys/data/eigen.h"

namespace softphys
{
namespace widget
{
class Widget
{
public:
  Widget();
  Widget(double x, double y, double width, double height);
  ~Widget();

  virtual void Move(double x, double y);
  virtual void Resize(double width, double height);
  virtual void Keyboard(int key, int action, int mods);
  virtual void MouseMove(double x, double y);
  virtual void MouseButton(int button, int action, int mods);

  virtual void Initialize();
  virtual void Draw();

  auto Position()
  {
    return position_;
  }

  auto Width()
  {
    return size_(0);
  }

  auto Height()
  {
    return size_(1);
  }

  auto ScreenPosition()
  {
    return screen_position_;
  }

  void SetScreenPosition(double x, double y)
  {
    screen_position_ = Vector2d(x, y);
  }

  void SetScreenPosition(const Vector2d& position)
  {
    screen_position_ = position;
  }

private:
  bool size_inherited_ = false;
  Vector2d position_;
  Vector2d screen_position_;
  Vector2d size_;
};
}
}

#endif // SOFTPHYS_WIDGET_WIDGET_H_
