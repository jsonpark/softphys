#include "softphys/widget/viewer.h"

#include "softphys/engine.h"
#include "softphys/viewer/painter.h"
#include "softphys/scene/scene_loader.h"
#include "softphys/model/visual/visual_sphere.h"
#include "softphys/model/visual/visual_cube.h"

namespace softphys
{
namespace widget
{
namespace
{
const double pi = 3.1415926535897932384626433832795;
}

Viewer::Viewer(Painter* painter)
  : Widget(painter),
  engine_(painter->GetEngine()),
  camera_(Camera::Type::Perspective)
{
  scene_ = std::make_shared<scene::Scene>();
}

Viewer::Viewer(Painter* painter, int x, int y, int width, int height)
  : Widget(painter, x, y, width, height),
  engine_(painter->GetEngine()),
  camera_(Camera::Type::Perspective)
{
  scene_ = std::make_shared<scene::Scene>();
}

Viewer::~Viewer()
{
}

void Viewer::Resize(double width, double height)
{
  Widget::Resize(width, height);
  camera_.SetAspect(width, height);
}

void Viewer::Keyboard(int key, int action, int mods)
{
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    animation_ = !animation_;
}

void Viewer::MouseMove(double x, double y)
{
  const auto& mouse = GetPainter()->GetMouse();

  double dx = x - mouse_last_x_;
  double dy = y - mouse_last_y_;

  bool left = mouse.IsPressed<Mouse::Button::LeftButton>();
  bool right = mouse.IsPressed<Mouse::Button::RightButton>();
  bool middle = mouse.IsPressed<Mouse::Button::MiddleButton>();

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

  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void Viewer::MouseButton(double x, double y, Mouse::Button button, Mouse::Status action, int mods)
{
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void Viewer::LoadScene(const std::string& filename)
{
  scene::SceneLoader loader;
  scene_ = loader.LoadFromJson(filename);
}

void Viewer::Initialize()
{
  // OpenGL
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(UINT32_MAX);

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

  sphere_model_ = std::make_unique<viewer::PolarSphereModel>(20);
  cylinder_model_ = std::make_unique<viewer::CylinderModel>(40);
  cone_model_ = std::make_unique<viewer::ConeModel>(20);
  cube_model_ = std::make_unique<viewer::CubeModel>();
  ground_model_ = std::make_unique<viewer::GroundModel>();

  // Timestamp
  timestamp_ = engine_->GetTime();
}

void Viewer::Draw()
{
  GetPainter()->SetViewport(ScreenPosition()(0), ScreenPosition()(1), Width(), Height());

  // Timestamp
  double now = engine_->GetTime();
  double time = now - timestamp_;
  timestamp_ = now;

  // Physics simulation
  auto physics = engine_->GetPhysics();
  if (animation_)
    physics->Simulate(time);

  // Setting camera
  ground_program_.SetCamera(camera_);

  light_program_.SetCamera(camera_);
  light_program_.SetLights(scene_->GetLights());

  // Display cylinder
  light_program_.Uniform1f("alpha", 1.0f);
  DrawAxis(Affine3d::Identity(), 1.0, 0.01);

  // Display physics objects
  light_program_.Uniform1f("alpha", 0.75f);
  auto models = engine_->GetModels();
  for (auto object : physics->GetObjects())
  {
    if (object->IsRigidBody())
    {
      auto rb = std::static_pointer_cast<physics::RigidBody>(object);
      const auto& position = rb->GetPosition();
      const auto& rotation = rb->GetOrientation().matrix();
      const auto& com = rb->GetCom();

      light_program_.Uniform1f("alpha", 1.0f);
      Affine3d rb_transform;
      rb_transform.setIdentity();
      rb_transform.translate(position);
      rb_transform.rotate(rotation);
      DrawAxis(rb_transform, 0.1, 0.002);
      light_program_.Uniform1f("alpha", 0.75f);

      if (rb->IsSphere())
      {
        auto visual_sphere = std::static_pointer_cast<model::VisualSphere>(engine_->GetModelFromPhysicsObject(object)->GetVisual());
        const auto radius = visual_sphere->Radius();
        // TODO: material name from model
        const auto& material_name = visual_sphere->MaterialName();
        const auto& material = models->GetMaterial(material_name);

        Eigen::Matrix4f model;
        model.block(0, 0, 3, 3) = (rotation * radius).cast<float>();
        model.block(3, 0, 1, 3).setZero();
        model.block(0, 3, 3, 1) = position.cast<float>();
        model(3, 3) = 1.f;

        light_program_.Use();
        light_program_.UniformMatrix4f("model", model);
        model.block(0, 3, 3, 1).setZero();
        light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose());
        light_program_.Uniform3f("material.ambient", material->Ambient());
        light_program_.Uniform3f("material.diffuse", material->Diffuse());
        light_program_.Uniform3f("material.specular", material->Specular());
        light_program_.Uniform1f("material.shininess", material->Shininess());

        sphere_model_->Draw();
      }

      else if (rb->IsCube())
      {
        auto visual_cube = std::static_pointer_cast<model::VisualCube>(engine_->GetModelFromPhysicsObject(object)->GetVisual());
        const auto size = visual_cube->Size();
        const auto& material_name = visual_cube->MaterialName();
        const auto& material = models->GetMaterial(material_name);

        Eigen::Affine3d model_transform;
        model_transform.setIdentity();
        model_transform.translate(position);
        model_transform.rotate(rotation);
        model_transform.scale(size.cast<double>());
        Eigen::Matrix4d model = model_transform.matrix();

        light_program_.Use();
        light_program_.UniformMatrix4f("model", model.cast<float>());
        model.block(0, 3, 3, 1).setZero();
        light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());
        light_program_.Uniform3f("material.ambient", material->Ambient());
        light_program_.Uniform3f("material.diffuse", material->Diffuse());
        light_program_.Uniform3f("material.specular", material->Specular());
        light_program_.Uniform1f("material.shininess", material->Shininess());

        cube_model_->Draw();
      }
    }

    else if (object->IsGround())
    {
      // TODO: rotate ground
      Eigen::Matrix4f model;
      model.setIdentity();

      ground_program_.Use();
      ground_program_.UniformMatrix4f("model", model);

      ground_model_->Draw();
    }
  }

  // Display physics simulator time
  double simulator_time = physics->GetTime();

  GetPainter()->RenderText(L"Time: " + std::to_wstring(simulator_time) + L"s", 0.f, 0.f, 0.12f, Eigen::Vector3f(0.f, 0.f, 0.f));
}

void Viewer::DrawAxis(const Affine3d& transform, double axis_length, double axis_radius)
{
  auto models = engine_->GetModels();

  Affine3d t;
  Matrix4d model;

  static const double cl = 0.8;

  light_program_.Use();

  // X axis
  t.setIdentity();
  t.scale(Vector3d(axis_length * cl / 2., axis_radius, axis_radius));
  t.translate(Vector3d(1.0, 0.0, 0.0));
  t.rotate(Eigen::AngleAxisd(pi / 2., Vector3d(0.0, 1.0, 0.0)));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  auto material = models->GetMaterial("red");
  light_program_.Uniform3f("material.ambient", material->Ambient());
  light_program_.Uniform3f("material.diffuse", material->Diffuse());
  light_program_.Uniform3f("material.specular", material->Specular());
  light_program_.Uniform1f("material.shininess", material->Shininess());

  cylinder_model_->Draw();

  t.setIdentity();
  t.translate(Vector3d(axis_length * cl, 0.0, 0.0));
  t.scale(Vector3d(axis_length * (1. - cl), axis_radius * 2., axis_radius * 2.));
  t.rotate(Eigen::AngleAxisd(pi / 2., Vector3d(0.0, 1.0, 0.0)));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  cone_model_->Draw();

  // Y axis
  t.setIdentity();
  t.scale(Vector3d(axis_radius, axis_length * cl / 2., axis_radius));
  t.translate(Vector3d(0.0, 1.0, 0.0));
  t.rotate(Eigen::AngleAxisd(pi / 2., Vector3d(-1.0, 0.0, 0.0)));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  material = models->GetMaterial("green");
  light_program_.Uniform3f("material.ambient", material->Ambient());
  light_program_.Uniform3f("material.diffuse", material->Diffuse());
  light_program_.Uniform3f("material.specular", material->Specular());
  light_program_.Uniform1f("material.shininess", material->Shininess());

  cylinder_model_->Draw();

  t.setIdentity();
  t.translate(Vector3d(0.0, axis_length * cl, 0.0));
  t.scale(Vector3d(axis_radius * 2., axis_length * (1. - cl), axis_radius * 2.));
  t.rotate(Eigen::AngleAxisd(pi / 2., Vector3d(-1.0, 0.0, 0.0)));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  cone_model_->Draw();

  // Z axis
  t.setIdentity();
  t.scale(Vector3d(axis_radius, axis_radius, axis_length * cl / 2.));
  t.translate(Vector3d(0.0, 0.0, 1.0));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  material = models->GetMaterial("blue");
  light_program_.Uniform3f("material.ambient", material->Ambient());
  light_program_.Uniform3f("material.diffuse", material->Diffuse());
  light_program_.Uniform3f("material.specular", material->Specular());
  light_program_.Uniform1f("material.shininess", material->Shininess());

  cylinder_model_->Draw();

  t.setIdentity();
  t.translate(Vector3d(0.0, 0.0, axis_length * cl));
  t.scale(Vector3d(axis_radius * 2., axis_radius * 2., axis_length * (1. - cl)));

  model = (transform * t).matrix();
  light_program_.UniformMatrix4f("model", model.cast<float>());
  model.block(0, 3, 3, 1).setZero();
  light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose().cast<float>());

  cone_model_->Draw();
}
}
}
