#ifndef SOFTPHYS_ENGINE_ENGINE_H_
#define SOFTPHYS_ENGINE_ENGINE_H_

#include <memory>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "softphys/engine/window.h"
#include "softphys/font/font_faces.h"

namespace softphys
{
// Hidden callbacks
namespace callbacks
{
Window* ToWindow(GLFWwindow* glfw_window);
void ResizeCallback(GLFWwindow* glfw_window, int width, int height);
void WindowPosCallback(GLFWwindow* glfw_window, int xpos, int ypos);
void CursorPosCallback(GLFWwindow* glfw_window, double xpos, double ypos);

// @window  The window that received the event.
// @button  The mouse button that was pressed or released.
// @action  One of GLFW_PRESS or GLFW_RELEASE.
// @mods  Bit field describing which modifier keys were held down.
void MouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods);
}

class Engine
{
public:
  Engine();
  ~Engine();

  Engine(const Engine& rhs) = delete;
  Engine& operator = (const Engine& rhs) = delete;

  Engine(Engine&& rhs) = default;
  Engine& operator = (Engine&& rhs) = default;

  template<class WindowType, typename ...Ts>
  std::shared_ptr<Window> CreateEngineWindow(Ts&& ... params)
  {
    std::shared_ptr<Window> window = std::make_shared<WindowType>(this, std::forward<Ts>(params)...);
    windows_.push_back(window);

    auto glfw_window = window->PointerToWindow();

    glfwSetWindowUserPointer(glfw_window, window.get());
    glfwSetFramebufferSizeCallback(glfw_window, callbacks::ResizeCallback);
    glfwSetWindowPosCallback(glfw_window, callbacks::WindowPosCallback);
    glfwSetCursorPosCallback(glfw_window, callbacks::CursorPosCallback);
    glfwSetMouseButtonCallback(glfw_window, callbacks::MouseButtonCallback);

    return window;
  }

  void Run();

  FontFace& LoadFont(const std::string& font);

private:
  bool ShouldClose();

  std::vector<std::shared_ptr<Window>> windows_;

  FontFaces font_faces_;
};
}

#endif // SOFTPHYS_ENGINE_ENGINE_H_
