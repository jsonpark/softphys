#include "softphys/widget/widget.h"

namespace softphys
{
namespace widget
{
Widget::Widget(Painter* painter)
  : painter_(painter), size_inherited_(true)
{
}

Widget::Widget(Painter* painter, double x, double y, double width, double height)
  : painter_(painter), size_inherited_(false),
  position_(x, y), size_(width, height)
{
}

Widget::~Widget() = default;

void Widget::Move(double x, double y)
{
  position_ = Vector2d(x, y);
}

void Widget::Resize(double width, double height)
{
  size_ = Vector2d(width, height);
}

void Widget::Keyboard(int key, int action, int mods)
{
}

void Widget::MouseMove(double x, double y)
{
}

void Widget::MouseButton(double x, double y, Mouse::Button button, Mouse::Status action, int mods)
{
}

void Widget::Initialize()
{
}

void Widget::Draw()
{
}
}
}
