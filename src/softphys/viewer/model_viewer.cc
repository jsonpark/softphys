#include "softphys/viewer/model_viewer.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "softphys/engine.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/sphere.h"
#include "softphys/scene/scene_loader.h"
#include "softphys/model/visual/visual_sphere.h"
#include "softphys/model/visual/visual_cube.h"
#include "softphys/data/eigen.h"

namespace softphys
{
ModelViewer::ModelViewer(Engine* engine, int x, int y, int width, int height)
  : ModelViewer(engine, "ModelViewer", x, y, width, height)
{
}

ModelViewer::ModelViewer(Engine* engine, const std::string& title, int x, int y, int width, int height)
  : Window(engine, title, x, y, width, height),
  camera_(Camera::Type::Perspective)
{
  scene_ = std::make_shared<scene::Scene>();
}

ModelViewer::~ModelViewer() = default;

void ModelViewer::Resize(int width, int height)
{
  Window::Resize(width, height);

  camera_.SetAspect(width, height);
}

void ModelViewer::Keyboard(int key, int action, int mods)
{
}

void ModelViewer::MouseMove(double x, double y)
{
  double dx = x - mouse_.X();
  double dy = y - mouse_.Y();

  bool left = mouse_.IsPressed<Mouse::Button::LeftButton>();
  bool right = mouse_.IsPressed<Mouse::Button::RightButton>();
  bool middle = mouse_.IsPressed<Mouse::Button::MiddleButton>();

  if (left && right)
  {
    // Zoom
    camera_.Zoom(dx, dy);
  }

  else if (left)
  {
    // Rotate
    camera_.Rotate(dx, dy);
  }

  else if (right)
  {
    // Translate
    camera_.Translate(dx, dy);
  }

  mouse_.SetPos(x, y);
}

void ModelViewer::MouseButton(int button, int action, int mods)
{
  Mouse::Button mouse_button;
  switch (button)
  {
  case GLFW_MOUSE_BUTTON_LEFT:
    mouse_button = Mouse::Button::LeftButton;
    break;
  case GLFW_MOUSE_BUTTON_RIGHT:
    mouse_button = Mouse::Button::RightButton;
    break;
  case GLFW_MOUSE_BUTTON_MIDDLE:
    mouse_button = Mouse::Button::MiddleButton;
    break;
  default:
    return;
  }

  Mouse::Status mouse_status;
  switch (action)
  {
  case GLFW_PRESS:
    mouse_status = Mouse::Status::Pressed;
    break;
  case GLFW_RELEASE:
    mouse_status = Mouse::Status::Released;
    break;
  default:
    return;
  }

  mouse_.SetStatus(mouse_button, mouse_status);
}

void ModelViewer::LoadScene(const std::string& filename)
{
  scene::SceneLoader loader;
  scene_ = loader.LoadFromJson(filename);
}

void ModelViewer::Initialize()
{
  const auto& engine = GetEngine();

  // OpenGL
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(UINT32_MAX);

  // Mouse
  double x;
  double y;

  glfwGetCursorPos(PointerToWindow(), &x, &y);

  mouse_.SetPos(x, y);
  mouse_.SetStatus(Mouse::Button::LeftButton, Mouse::Status::Released);
  mouse_.SetStatus(Mouse::Button::RightButton, Mouse::Status::Released);
  mouse_.SetStatus(Mouse::Button::MiddleButton, Mouse::Status::Released);

  // Shaders
  ground_program_.Attach(GlShader("..\\src\\shader\\ground.vert"));
  ground_program_.Attach(GlShader("..\\src\\shader\\ground.frag"));
  ground_program_.Link();

  ground_program_.Use();
  ground_program_.Uniform2f("max_distance", 9.f, 15.f);

  light_program_.Attach(GlShader("..\\src\\shader\\light.vert"));
  light_program_.Attach(GlShader("..\\src\\shader\\light.frag"));
  light_program_.Link();

  light_program_.Use();
  light_program_.Uniform2f("max_distance", 9.f, 15.f);

  // Scene
  camera_.SetNear(0.001);

  ground_model_ = std::make_unique<viewer::GroundModel>();
}

void ModelViewer::Display()
{
  const auto& engine = GetEngine();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Setting camera
  ground_program_.Use();
  ground_program_.UniformMatrix4f("projection", camera_.Projectionf());
  ground_program_.UniformMatrix4f("view", camera_.Viewf());
  ground_program_.Uniform3f("eye", camera_.GetEye().cast<float>());

  light_program_.SetCamera(camera_);
  light_program_.SetLights(scene_->GetLights());
  light_program_.Uniform3f("eye", camera_.GetEye().cast<float>());

  // Ground rendering
  Eigen::Matrix4f model;
  model.setIdentity();

  ground_program_.Use();
  ground_program_.UniformMatrix4f("model", model);

  ground_model_->Draw();
}
}
