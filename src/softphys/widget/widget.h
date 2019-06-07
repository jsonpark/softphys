#ifndef SOFTPHYS_WIDGET_WIDGET_H_
#define SOFTPHYS_WIDGET_WIDGET_H_

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

  virtual void Resize(int width, int height);
  virtual void Keyboard(int key, int action, int mods);
  virtual void MouseMove(double x, double y);
  virtual void MouseButton(int button, int action, int mods);

  virtual void Initialize();
  virtual void Draw();

  auto Width()
  {
    return size_.width;
  }

  auto Height()
  {
    return size_.height;
  }

private:
  struct Size
  {
    Size() = default;
    Size(double x, double y, double width, double height)
      : x(x), y(y), width(width), height(height)
    {
    }

    double x = 0.;
    double y = 0.;
    double width = 100.;
    double height = 100.;
  };

  bool size_inherited_ = false;
  Size size_;
};
}
}

#endif // SOFTPHYS_WIDGET_WIDGET_H_
