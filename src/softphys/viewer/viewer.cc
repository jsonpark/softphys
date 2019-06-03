#include "softphys/viewer/viewer.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "softphys/engine.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/primitive_sphere.h"
#include "softphys/scene/scene_loader.h"
#include "softphys/model/primitive/sphere.h"
#include "softphys/physics/physics_loader.h"
#include "softphys/model/modelset_loader.h"

namespace softphys
{
Viewer::Viewer(Engine* engine, int x, int y, int width, int height)
  : Window(engine, x, y, width, height),
  camera_(Camera::Type::Perspective)
{
  scene_ = std::make_shared<scene::Scene>();
}

Viewer::~Viewer()
{
}

void Viewer::DisplayPhysicsScene(std::unique_ptr<Physics> physics)
{
  physics_ = std::move(physics);
}

void Viewer::Resize(int width, int height)
{
  Window::Resize(width, height);

  camera_.SetAspect(width, height);
}

void Viewer::Keyboard(int key, int action, int mods)
{
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    animation_ = !animation_;
}

void Viewer::MouseMove(double x, double y)
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

void Viewer::MouseButton(int button, int action, int mods)
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

void Viewer::LoadModels(const std::string& filename)
{
  model::ModelsetLoader loader;
  modelset_ = loader.LoadFromJson(filename);
}

void Viewer::LoadScene(const std::string& filename)
{
  scene::SceneLoader loader;
  scene_ = loader.LoadFromJson(filename);
}

void Viewer::LoadPhysics(const std::string& filename)
{
  PhysicsLoader loader;
  physics_ = loader.LoadFromJson(filename, modelset_);
}

void Viewer::Initialize()
{
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
  texture_program_.Attach(GlVertexShader("..\\src\\shader\\texture.vert"));
  texture_program_.Attach(GlFragmentShader("..\\src\\shader\\texture.frag"));
  texture_program_.Link();

  texture_program_.Use();
  texture_program_.Uniform1i("texture_image1", 0);
  texture_program_.Uniform1i("texture_image2", 1);

  uniform_color_program_.Attach(GlVertexShader("..\\src\\shader\\uniform_color.vert"));
  uniform_color_program_.Attach(GlFragmentShader("..\\src\\shader\\uniform_color.frag"));
  uniform_color_program_.Link();

  ground_program_.Attach(GlVertexShader("..\\src\\shader\\ground.vert"));
  ground_program_.Attach(GlFragmentShader("..\\src\\shader\\ground.frag"));
  ground_program_.Link();

  ground_program_.Use();
  ground_program_.Uniform2f("max_distance", 9.f, 10.f);

  light_program_.Attach(GlVertexShader("..\\src\\shader\\light.vert"));
  light_program_.Attach(GlFragmentShader("..\\src\\shader\\light.frag"));
  light_program_.Link();

  light_program_.Use();
  light_program_.Uniform2f("max_distance", 9.f, 10.f);

  // Scene
  camera_.SetNear(0.001);

  sphere_model_ = std::make_unique<viewer::PolarSphereModel>(20);
  ground_model_ = std::make_unique<viewer::GroundModel>();

  // Text rendering preparation
  text_program_.Attach(GlVertexShader("..\\src\\shader\\text.vert"));
  text_program_.Attach(GlFragmentShader("..\\src\\shader\\text.frag"));
  text_program_.Link();

  text_program_.Use();
  text_program_.Uniform1i("glyph", 0);

  glyph_buffer_ = GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw>(16);

  glyph_array_.VertexAttribPointer(0, 4, glyph_buffer_);

  glyphs_ = GlGlyphs(GetEngine()->LoadFont("consola"));

  // Timestamp
  timestamp_ = GetEngine()->GetTime();

  // Test cubemap texture
  xp_texture_ = std::make_shared<Texture<>>("..\\textures\\xp.png");
  xn_texture_ = std::make_shared<Texture<>>("..\\textures\\xn.png");
  yp_texture_ = std::make_shared<Texture<>>("..\\textures\\yp.png");
  yn_texture_ = std::make_shared<Texture<>>("..\\textures\\yn.png");
  zp_texture_ = std::make_shared<Texture<>>("..\\textures\\zp.png");
  zn_texture_ = std::make_shared<Texture<>>("..\\textures\\zn.png");
  std::vector<std::shared_ptr<Texture<>>> cubemap = {
    xp_texture_,
    xn_texture_,
    yp_texture_,
    yn_texture_,
    zp_texture_,
    zn_texture_
  };
  face_cubemap_ = std::make_unique<GlTextureCubeMap>(cubemap);

  light_cubemap_program_.Attach(GlVertexShader("..\\src\\shader\\light_cubemap.vert"));
  light_cubemap_program_.Attach(GlFragmentShader("..\\src\\shader\\light_cubemap.frag"));
  light_cubemap_program_.Link();

  light_cubemap_program_.Use();
  light_cubemap_program_.Uniform2f("max_distance", 9.f, 10.f);
}

void Viewer::Display()
{
  // Timestamp
  double now = GetEngine()->GetTime();
  double time = now - timestamp_;
  timestamp_ = now;

  // Physics simulation
  if (animation_)
    physics_->Simulate(time);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Setting camera
  texture_program_.Use();
  texture_program_.UniformMatrix4f("projection", camera_.Projectionf());
  texture_program_.UniformMatrix4f("view", camera_.Viewf());

  // Display physics objects
  ground_program_.Use();
  ground_program_.UniformMatrix4f("projection", camera_.Projectionf());
  ground_program_.UniformMatrix4f("view", camera_.Viewf());
  ground_program_.Uniform3f("eye", camera_.GetEye().cast<float>());

  light_program_.Use();
  light_program_.UniformMatrix4f("projection", camera_.Projectionf());
  light_program_.UniformMatrix4f("view", camera_.Viewf());

  Eigen::Vector3f eye = camera_.GetEye().cast<float>();
  light_program_.Uniform3f("eye", eye);

  const auto& lights = scene_->GetLights();
  for (int i = 0; i < lights.size() && i < scene::Scene::max_lights; i++)
  {
    const auto& light = lights[i];

    std::string name = "lights[" + std::to_string(i) + "]";
    light_program_.Uniform1i(name + ".use", 1);

    switch (light.type)
    {
    case Light::Type::Directional:
      light_program_.Uniform1i(name + ".type", 0);
      break;
    case Light::Type::Point:
      light_program_.Uniform1i(name + ".type", 1);
      break;
    default:
      light_program_.Uniform1i(name + ".type", 2);
      break;
    }

    light_program_.Uniform3f(name + ".position", light.position);
    light_program_.Uniform3f(name + ".ambient", light.ambient);
    light_program_.Uniform3f(name + ".diffuse", light.diffuse);
    light_program_.Uniform3f(name + ".specular", light.specular);
  }
  for (int i = lights.size(); i < scene::Scene::max_lights; i++)
    light_program_.Uniform1i("lights[" + std::to_string(i) + "].use", 0);


  light_cubemap_program_.Use();
  light_cubemap_program_.UniformMatrix4f("projection", camera_.Projectionf());
  light_cubemap_program_.UniformMatrix4f("view", camera_.Viewf());

  for (int i = 0; i < lights.size() && i < scene::Scene::max_lights; i++)
  {
    const auto& light = lights[i];

    std::string name = "lights[" + std::to_string(i) + "]";
    light_cubemap_program_.Uniform1i(name + ".use", 1);

    switch (light.type)
    {
    case Light::Type::Directional:
      light_cubemap_program_.Uniform1i(name + ".type", 0);
      break;
    case Light::Type::Point:
      light_cubemap_program_.Uniform1i(name + ".type", 1);
      break;
    default:
      light_cubemap_program_.Uniform1i(name + ".type", 2);
      break;
    }

    light_cubemap_program_.Uniform3f(name + ".position", light.position);
    light_cubemap_program_.Uniform3f(name + ".ambient", light.ambient);
    light_cubemap_program_.Uniform3f(name + ".diffuse", light.diffuse);
    light_cubemap_program_.Uniform3f(name + ".specular", light.specular);
  }
  for (int i = lights.size(); i < scene::Scene::max_lights; i++)
    light_cubemap_program_.Uniform1i("lights[" + std::to_string(i) + "].use", 0);

  uniform_color_program_.Use();
  uniform_color_program_.UniformMatrix4f("projection", camera_.Projectionf());
  uniform_color_program_.UniformMatrix4f("view", camera_.Viewf());

  for (auto object : physics_->GetObjects())
  {
    if (object->IsRigidBody())
    {
      auto rb = std::static_pointer_cast<RigidBody>(object);
      const auto& primitives = rb->GetPrimitives();
      const auto& transforms = rb->GetTransforms();

      const auto& position = rb->GetPosition();
      const auto& rotation = rb->GetOrientation().matrix();
      const auto& com = rb->GetCom();

      for (int i = 0; i < primitives.size(); i++)
      {
        auto primitive = primitives[i];
        auto transform = transforms[i];

        if (primitive->IsSphere())
        {
          auto sphere = std::static_pointer_cast<PrimitiveSphere>(primitive);
          auto r = sphere->Radius();

          Eigen::Matrix4f model;
          model.block(0, 0, 3, 3) = (rotation * r).cast<float>();
          model.block(3, 0, 1, 3).setZero();
          model.block(0, 3, 3, 1) = (position + transform.translation()).cast<float>();
          model(3, 3) = 1.f;

          auto model_sphere = std::static_pointer_cast<model::Sphere>(sphere->ModelPrimitive());
          const auto& material_name = model_sphere->MaterialName();
          const auto& material = modelset_->GetMaterial(material_name);

          /*
          light_program_.Use();
          light_program_.UniformMatrix4f("model", model);
          model.block(0, 3, 3, 1).setZero();
          light_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose());
          light_program_.Uniform3f("material.ambient", material->Ambient());
          light_program_.Uniform3f("material.diffuse", material->Diffuse());
          light_program_.Uniform3f("material.specular", material->Specular());
          light_program_.Uniform1f("material.shininess", material->Shininess());
          */

          light_cubemap_program_.Use();
          light_cubemap_program_.UniformMatrix4f("model", model);
          model.block(0, 3, 3, 1).setZero();
          light_cubemap_program_.UniformMatrix4f("model_inv_transpose", model.inverse().transpose());
          light_cubemap_program_.Uniform3f("material.ambient", material->Ambient());
          light_cubemap_program_.Uniform1i("material.diffuse_texture", 0);
          light_cubemap_program_.Uniform3f("material.specular", material->Specular());
          light_cubemap_program_.Uniform1f("material.shininess", material->Shininess());

          face_cubemap_->Bind();
          sphere_model_->Draw();
        }
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
  float w = Width();
  float h = Height();
  Eigen::Matrix4f font_projection;
  font_projection.setZero();
  font_projection(0, 0) = 2.f / w;
  font_projection(1, 1) = 2.f / h;
  font_projection(2, 2) = 1.f;
  font_projection(3, 3) = 1.f;

  text_program_.Use();
  text_program_.UniformMatrix4f("projection", font_projection);

  double simulator_time = physics_->GetTime();

  RenderText(L"Time: " + std::to_wstring(simulator_time) + L"s", -w / 2.f + 10.f, h / 2.f - 20, 0.12f, Eigen::Vector3f(0.f, 0.f, 0.f));
}

void Viewer::RenderText(const std::wstring& s, float x, float y, float font_size, Eigen::Vector3f color)
{
  glDisable(GL_DEPTH_TEST);

  // Activate corresponding render state
  text_program_.Use();
  text_program_.Uniform3f("text_color", color);

  glyph_array_.Bind();
  
  float original_x = x;

  // Iterate through all characters
  for (auto c = s.begin(); c != s.end(); c++)
  {
    if (*c == L'\n')
    {
      x = original_x;
      y -= 128 * font_size;
      continue;
    }

    const auto& glyph_size = glyphs_.GetGlyphSize(*c);
    auto& glyph_texture = glyphs_.GetTexture(*c);

    float xpos = x + glyph_size.bearing_x * font_size;
    float ypos = y - (glyph_size.height - glyph_size.bearing_y) * font_size;

    float w = glyph_size.width * font_size;
    float h = glyph_size.height * font_size;

    // Update VBO for each character
    std::vector<float> vertices{
        xpos,     ypos,       0.0f, 1.0f,
        xpos + w, ypos,       1.0f, 1.0f,
        xpos,     ypos + h,   0.0f, 0.0f,
        xpos + w, ypos + h,   1.0f, 0.0f
    };

    // Render glyph texture over quad
    glyph_texture.Bind(0);

    // Update content of VBO memory
    glyph_buffer_.BufferSubData(vertices);

    // Render quad
    glyph_array_.DrawArrays(GlVertexArray::DrawType::TriangleStrip, 4);

    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (glyph_size.advance >> 6) * font_size; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }

  glEnable(GL_DEPTH_TEST);
}
}
