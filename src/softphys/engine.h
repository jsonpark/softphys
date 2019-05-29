#ifndef SOFTPHYS_ENGINE_H_
#define SOFTPHYS_ENGINE_H_

#include <memory>
#include <unordered_map>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "softphys/viewer/window.h"
#include "softphys/font/font_faces.h"

namespace softphys
{
// Hidden callbacks
namespace callbacks
{
Window* ToWindow(GLFWwindow* glfw_window);
void ResizeCallback(GLFWwindow* glfw_window, int width, int height);
void WindowPosCallback(GLFWwindow* glfw_window, int xpos, int ypos);
void KeyCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
void CursorPosCallback(GLFWwindow* glfw_window, double xpos, double ypos);

// @window  The window that received the event.
// @button  The mouse button that was pressed or released.
// @action  One of GLFW_PRESS or GLFW_RELEASE.
// @mods  Bit field describing which modifier keys were held down.
void MouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods);
}

class Engine
{
private:
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = Clock::time_point;
  using Duration = std::chrono::duration<double>;

public:
  Engine();
  ~Engine();

  Engine(const Engine& rhs) = delete;
  Engine& operator = (const Engine& rhs) = delete;

  Engine(Engine&& rhs) = default;
  Engine& operator = (Engine&& rhs) = default;

  template<class WindowType, typename ...Ts>
  std::shared_ptr<WindowType> CreateEngineWindow(Ts&& ... params)
  {
    std::shared_ptr<WindowType> window = std::make_shared<WindowType>(this, std::forward<Ts>(params)...);
    windows_.push_back(window);

    auto glfw_window = window->PointerToWindow();

    glfwSetWindowUserPointer(glfw_window, window.get());
    glfwSetFramebufferSizeCallback(glfw_window, callbacks::ResizeCallback);
    glfwSetWindowPosCallback(glfw_window, callbacks::WindowPosCallback);
    glfwSetCursorPosCallback(glfw_window, callbacks::CursorPosCallback);
    glfwSetMouseButtonCallback(glfw_window, callbacks::MouseButtonCallback);
    glfwSetKeyCallback(glfw_window, callbacks::KeyCallback);

    return window;
  }

  void Run();

  double GetTime();

  FontFace& LoadFont(const std::string& font);

private:
  bool ShouldClose();

  std::vector<std::shared_ptr<Window>> windows_;

  FontFaces font_faces_;

  TimePoint start_time_;
};
}

#endif // SOFTPHYS_ENGINE_H_
