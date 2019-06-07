#ifndef SOFTPHYS_VIEWER_MOUSE_H_
#define SOFTPHYS_VIEWER_MOUSE_H_

#include <vector>

namespace softphys
{
class Mouse
{
public:
  enum class Button : std::uint8_t
  {
    LeftButton,
    MiddleButton,
    RightButton,
    NumButtons,
  };

  enum class Status
  {
    Pressed,
    Released,
  };

private:
  template<Button button>
  static constexpr auto ButtonToIndex() noexcept
  {
    return static_cast<std::underlying_type_t<Button>>(button);
  }

  static auto ButtonToIndex(Button button) noexcept
  {
    return static_cast<std::underlying_type_t<Button>>(button);
  }


public:
  Mouse();

  void SetPos(double x, double y) noexcept
  {
    x_ = x;
    y_ = y;
  }

  auto X() const noexcept
  {
    return x_;
  }

  auto Y() const noexcept
  {
    return y_;
  }

  void SetStatus(Button button, Status status)
  {
    buttons_[ButtonToIndex(button)] = status;
  }

  template<Button button>
  bool IsPressed() const noexcept
  {
    return buttons_[ButtonToIndex(button)] == Status::Pressed;
  }

  bool IsDragging() const noexcept;

private:
  double x_;
  double y_;
  std::vector<Status> buttons_;
};
}

#endif // SOFTPHYS_VIEWER_MOUSE_H_
