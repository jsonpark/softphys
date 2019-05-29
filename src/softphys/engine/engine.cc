#include "softphys/engine/engine.h"

#include <iostream>

#include "viewer/viewer.h"

namespace softphys
{
// Hidden callbacks
namespace callbacks
{
Window* ToWindow(GLFWwindow* glfw_window)
{
  return static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
}

void ResizeCallback(GLFWwindow* glfw_window, int width, int height)
{
  auto window = ToWindow(glfw_window);
  window->Resize(width, height);
}

void WindowPosCallback(GLFWwindow* glfw_window, int xpos, int ypos)
{
  auto window = ToWindow(glfw_window);
  window->Move(xpos, ypos);
}

void CursorPosCallback(GLFWwindow* glfw_window, double xpos, double ypos)
{
  auto window = ToWindow(glfw_window);
  window->MouseMove(xpos, ypos);
}

// @window  The window that received the event.
// @button  The mouse button that was pressed or released.
// @action  One of GLFW_PRESS or GLFW_RELEASE.
// @mods  Bit field describing which modifier keys were held down.
void MouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods)
{
  auto window = ToWindow(glfw_window);
  window->MouseButton(button, action, mods);
}
}

Engine::Engine()
{
  glfwInit();
}

Engine::~Engine()
{
  glfwTerminate();
}

FontFace& Engine::LoadFont(const std::string& font)
{
  return font_faces_.Load(font);
}

bool Engine::ShouldClose()
{
  for (int i = 0; i < windows_.size(); i++)
  {
    auto window = windows_[i];

    if (window->ShouldClose())
    {
      for (int j = i; j < windows_.size() - 1; j++)
        windows_[j] = windows_[j + 1];
      windows_.pop_back();
      i--;
    }
  }

  return windows_.empty();
}

void Engine::Run()
{
  for (const auto& window : windows_)
  {
    window->MakeCurrent();
    window->Initialize();
  }

  while (!ShouldClose())
  {
    for (const auto& window : windows_)
    {
      window->MakeCurrent();
      window->Display();
    }

    for (const auto& window : windows_)
    {
      window->MakeCurrent();
      window->SwapBuffers();
    }

    glfwPollEvents();
  }
}
}
