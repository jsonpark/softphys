#include "softphys/widget/widget.h"

namespace softphys
{
namespace widget
{
Widget::Widget()
  : size_inherited_(true)
{
}

Widget::Widget(double x, double y, double width, double height)
  : size_inherited_(false),
  size_(x, y, width, height)
{
}

Widget::~Widget() = default;

void Widget::Resize(int width, int height)
{
  size_.width = width;
  size_.height = height;
}

void Widget::Keyboard(int key, int action, int mods)
{
}

void Widget::MouseMove(double x, double y)
{
}

void Widget::MouseButton(int button, int action, int mods)
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
