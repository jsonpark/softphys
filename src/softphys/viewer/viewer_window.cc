#include "softphys/viewer/viewer_window.h"

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
namespace
{
const double pi = 3.1415926535897932384626433832795;
}

ViewerWindow::ViewerWindow(Engine* engine, int x, int y, int width, int height)
  : ViewerWindow(engine, "Viewer", x, y, width, height)
{
}

ViewerWindow::ViewerWindow(Engine* engine, const std::string& title, int x, int y, int width, int height)
  : Window(engine, title, x, y, width, height)
{
  viewer_ = std::make_unique<widget::Viewer>(GetEngine());
}

ViewerWindow::~ViewerWindow()
{
}

void ViewerWindow::Resize(int width, int height)
{
  viewer_->Resize(width, height);
}

void ViewerWindow::Keyboard(int key, int action, int mods)
{
  viewer_->Keyboard(key, action, mods);
}

void ViewerWindow::MouseMove(double x, double y)
{
  viewer_->MouseMove(x, y);
}

void ViewerWindow::MouseButton(int button, int action, int mods)
{
  viewer_->MouseButton(button, action, mods);
}

void ViewerWindow::LoadScene(const std::string& filename)
{
  viewer_->LoadScene(filename);
}

void ViewerWindow::Initialize()
{
  viewer_->Initialize();
}

void ViewerWindow::Display()
{
  viewer_->Resize(Width(), Height());
  viewer_->Draw();
}
}
