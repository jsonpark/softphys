#include "softphys/viewer/viewer.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "softphys/engine.h"

namespace softphys
{
Viewer::Viewer(Engine* engine, int x, int y, int width, int height)
  : Window(engine, x, y, width, height),
  camera_(Camera::Type::Perspective)
{
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

void Viewer::Initialize()
{
  // OpenGL
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
  glEnable(GL_MULTISAMPLE);

  // Mouse
  double x;
  double y;

  glfwGetCursorPos(PointerToWindow(), &x, &y);

  mouse_.SetPos(x, y);
  mouse_.SetStatus(Mouse::Button::LeftButton, Mouse::Status::Released);
  mouse_.SetStatus(Mouse::Button::RightButton, Mouse::Status::Released);
  mouse_.SetStatus(Mouse::Button::MiddleButton, Mouse::Status::Released);

  // Scene
  std::vector<float> vertices = {
    // positions          // colors           // texture coords
    -1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
     1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
     1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
    -1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
  };
  std::vector<unsigned int> indices = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };
  Texture<> texture1("..\\textures\\container.png");
  Texture<> texture2("..\\textures\\awesomeface.png");

  vertex_buffer_ = GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw>(vertices);
  index_buffer_ = GlBuffer<unsigned int, GlBufferTarget::ElementArrayBuffer, GlBufferUsage::StaticDraw>(indices);

  vertex_array_.VertexAttribPointer(0, 3, vertex_buffer_, 8, 0);
  vertex_array_.VertexAttribPointer(1, 3, vertex_buffer_, 8, 3);
  vertex_array_.VertexAttribPointer(2, 2, vertex_buffer_, 8, 6);

  std::vector<float> axis_vertices = {
    0.f, 0.f, 0.f,  1.f, 0.f, 0.f,
    1.f, 0.f, 0.f,  1.f, 0.f, 0.f,
    0.f, 0.f, 0.f,  0.f, 1.f, 0.f,
    0.f, 1.f, 0.f,  0.f, 1.f, 0.f,
    0.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,  0.f, 0.f, 1.f,
  };

  axis_buffer_ = GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::StaticDraw>(axis_vertices);

  axis_vertex_array_.VertexAttribPointer(0, 3, axis_buffer_, 6, 0);
  axis_vertex_array_.VertexAttribPointer(1, 3, axis_buffer_, 6, 3);

  texture_program_.Attach(GlVertexShader("..\\src\\shader\\texture.vert"));
  texture_program_.Attach(GlFragmentShader("..\\src\\shader\\texture.frag"));
  texture_program_.Link();

  gl_texture1_ = GlTexture<GlTextureType::Texture2D>(texture1);
  gl_texture2_ = GlTexture<GlTextureType::Texture2D>(texture2);

  texture_program_.Use();
  texture_program_.Uniform("texture_image1", 0);
  texture_program_.Uniform("texture_image2", 1);

  camera_.SetNear(0.001);

  // Text rendering preparation
  text_program_.Attach(GlVertexShader("..\\src\\shader\\text.vert"));
  text_program_.Attach(GlFragmentShader("..\\src\\shader\\text.frag"));
  text_program_.Link();

  text_program_.Use();
  text_program_.Uniform("glyph", 0);

  glyph_buffer_ = GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw>(16);

  glyph_array_.VertexAttribPointer(0, 4, glyph_buffer_);

  glyphs_ = GlGlyphs(GetEngine()->LoadFont("consola"));

  // Timestamp
  timestamp_ = GetEngine()->GetTime();
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
  texture_program_.Uniform("projection", camera_.Projectionf());
  texture_program_.Uniform("view", camera_.Viewf());

  // Display physics objects

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
  text_program_.Uniform("projection", font_projection);

  double simulator_time = physics_->GetTime();

  RenderText(L"Time: " + std::to_wstring(simulator_time) + L"s", -w / 2.f + 10.f, h / 2.f - 20, 0.12f, Eigen::Vector3f(0.f, 0.f, 0.f));
}

void Viewer::RenderText(const std::wstring& s, float x, float y, float font_size, Eigen::Vector3f color)
{
  glDisable(GL_DEPTH_TEST);

  // Activate corresponding render state
  text_program_.Use();
  text_program_.Uniform("text_color", color(0), color(1), color(2));

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
