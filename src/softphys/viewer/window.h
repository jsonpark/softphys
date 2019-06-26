#ifndef SOFTPHYS_VIEWER_WINDOW_H_
#define SOFTPHYS_VIEWER_WINDOW_H_

#include <memory>
#include <string>

#include "softphys/viewer/mouse.h"
#include "softphys/viewer/mouse_event.h"

struct GLFWwindow;

namespace softphys
{
class Engine;

class Window
{
  friend class Engine;

public:
  Window() = delete;
  Window(Engine* engine, int x, int y, int width, int height);
  Window(Engine* engine, const std::string& title, int x, int y, int width, int height);
  virtual ~Window();

  Window(const Window& rhs) = delete;
  Window& operator = (const Window& rhs) = delete;

  Window(Window&& rhs) = default;
  Window& operator = (Window&& rhs) = default;

  auto Width() const noexcept
  {
    return width_;
  }

  auto Height() const noexcept
  {
    return height_;
  }

  auto GetEngine() const
  {
    return engine_;
  }

  bool ShouldClose();
  void SetTitle(const std::string& title);

  virtual void Resize(int width, int height);
  virtual void Move(int x, int y);
  virtual void Keyboard(int key, int action, int mods);
  virtual void MouseMove(double x, double y);
  virtual void MouseButton(Mouse::Button button, Mouse::Status action, int mods);

  virtual void Initialize();
  virtual void Display();

protected:
  auto PointerToWindow() const
  {
    return window_;
  }

private:
  void MakeCurrent();
  void SwapBuffers();

  GLFWwindow* window_;
  Engine* engine_;

  int x_;
  int y_;
  int width_;
  int height_;
};
}

#endif // SOFTPHYS_VIEWER_WINDOW_H_
