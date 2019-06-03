#include "softphys/viewer/window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "softphys/data/texture.h"
#include "softphys/viewer/gl_texture.h"
#include "softphys/viewer/gl_buffer.h"
#include "softphys/viewer/gl_program.h"
#include "softphys/viewer/gl_shader.h"
#include "softphys/viewer/gl_vertex_array.h"

namespace softphys
{
Window::Window(Engine* engine, int x, int y, int width, int height)
  : engine_(engine), x_(x), y_(y), width_(width), height_(height), window_(nullptr)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  window_ = glfwCreateWindow(width, height, "SoftPhys", NULL, NULL);
  if (window_ == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwSetWindowPos(window_, x, y);

  MakeCurrent();
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }
}

Window::~Window()
{
  glfwDestroyWindow(window_);
}

void Window::MakeCurrent()
{
  glfwMakeContextCurrent(window_);
}

bool Window::ShouldClose()
{
  return glfwWindowShouldClose(window_);
}

void Window::SwapBuffers()
{
  glfwSwapBuffers(window_);
}

void Window::Resize(int width, int height)
{
  width_ = width;
  height_ = height;

  glViewport(0, 0, width, height);
}

void Window::Move(int x, int y)
{
  x_ = x;
  y_ = y;
}

void Window::Keyboard(int key, int action, int mods)
{
}

void Window::MouseMove(double x, double y)
{
}

void Window::MouseButton(int button, int action, int mods)
{
}

void Window::Initialize()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void Window::Display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
}
