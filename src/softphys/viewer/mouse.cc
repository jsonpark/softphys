#include "softphys/viewer/mouse.h"

namespace softphys
{
Mouse::Mouse()
  : x_(0.), y_(0.),
  buttons_(static_cast<int>(Button::NumButtons), Status::Released)
{
}

bool Mouse::IsDragging() const noexcept
{
  return IsPressed<Button::LeftButton>() || IsPressed<Button::RightButton>() || IsPressed<Button::MiddleButton>();
}
}
