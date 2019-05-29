#ifndef SOFTPHYS_ENGINE_MOUSE_EVENT_H_
#define SOFTPHYS_ENGINE_MOUSE_EVENT_H_

#include "softphys/engine/mouse.h"

namespace softphys
{
class MouseEvent
{
public:
  MouseEvent() = default;

  virtual bool IsMoveEvent() const noexcept
  {
    return false;
  }

  virtual bool IsButtonEvent() const noexcept
  {
    return false;
  }

private:
};

class MouseMoveEvent : public MouseEvent
{
public:
  MouseMoveEvent() = delete;

  MouseMoveEvent(double x, double y)
    : x_(x), y_(y)
  {
  }

  bool IsMoveEvent() const noexcept override
  {
    return true;
  }

  auto X() const noexcept
  {
    return x_;
  }

  auto Y() const noexcept
  {
    return y_;
  }

private:
  double x_;
  double y_;
};

class MouseButtonEvent : public MouseEvent
{
public:
  MouseButtonEvent() = delete;

  MouseButtonEvent(Mouse::Button button, Mouse::Status status)
    : button_(button), status_(status)
  {
  }

  bool IsButtonEvent() const noexcept override
  {
    return true;
  }

  auto Button() const noexcept
  {
    return button_;
  }

  auto Status() const noexcept
  {
    return status_;
  }

private:
  Mouse::Button button_;
  Mouse::Status status_;
};
}

#endif // SOFTPHYS_ENGINE_MOUSE_EVENT_H_
