#ifndef SOFTPHYS_WIDGET_WIDGET_H_
#define SOFTPHYS_WIDGET_WIDGET_H_

#include "softphys/data/eigen.h"
#include "softphys/viewer/mouse.h"

namespace softphys
{
class Painter;

namespace widget
{
class Widget
{
public:
  Widget() = delete;
  Widget(Painter* painter);
  Widget(Painter* painter, double x, double y, double width, double height);
  ~Widget();

  virtual void Move(double x, double y);
  virtual void Resize(double width, double height);
  virtual void Keyboard(int key, int action, int mods);
  virtual void MouseMove(double x, double y);
  virtual void MouseButton(double x, double y, Mouse::Button button, Mouse::Status action, int mods);

  virtual void Initialize();
  virtual void Draw();

  const auto& Position() const noexcept
  {
    return position_;
  }

  const auto& Size() const noexcept
  {
    return size_;
  }

  auto Width() const noexcept
  {
    return size_(0);
  }

  auto Height() const noexcept
  {
    return size_(1);
  }

  auto ScreenPosition() const noexcept
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

  auto GetPainter() const noexcept
  {
    return painter_;
  }

private:
  Painter* painter_;

  bool size_inherited_ = false;
  Vector2d position_;
  Vector2d screen_position_;
  Vector2d size_;
};
}
}

#endif // SOFTPHYS_WIDGET_WIDGET_H_
