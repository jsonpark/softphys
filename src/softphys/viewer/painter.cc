#include "softphys/viewer/painter.h"

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

Painter::Painter(Engine* engine, int x, int y, int width, int height)
  : Painter(engine, "Painter", x, y, width, height)
{
}

Painter::Painter(Engine* engine, const std::string& title, int x, int y, int width, int height)
  : Window(engine, title, x, y, width, height)
{
  viewer_ = std::make_shared<widget::Viewer>(this);
  treeview_ = std::make_shared<widget::Treeview>(this);
  splitview_ = std::make_shared<widget::Splitview>(this, widget::Splitview::Split::Vertical, treeview_, viewer_, 0.2);
}

Painter::~Painter()
{
}

void Painter::Resize(int width, int height)
{
  Window::Resize(width, height);
}

void Painter::Keyboard(int key, int action, int mods)
{
  splitview_->Keyboard(key, action, mods);
}

void Painter::MouseMove(double x, double y)
{
  // Event process
  splitview_->MouseMove(x, y);

  // Mouse update
  mouse_.SetPos(x, y);
}

void Painter::MouseButton(Mouse::Button button, Mouse::Status action, int mods)
{
  // Event process
  double x, y;
  glfwGetCursorPos(PointerToWindow(), &x, &y);
  splitview_->MouseButton(x, y, button, action, mods);

  // Mouse update
  mouse_.SetStatus(button, action);
}

void Painter::LoadScene(const std::string& filename)
{
  viewer_->LoadScene(filename);
}

void Painter::Initialize()
{
  Window::Initialize();

  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

  // Text rendering preparation
  text_program_.Attach(GlShader("..\\src\\shader\\text.vert"));
  text_program_.Attach(GlShader("..\\src\\shader\\text.frag"));
  text_program_.Link();

  text_program_.Use();
  text_program_.Uniform1i("glyph", 0);

  glyph_buffer_ = GlBuffer<float, GlBufferTarget::ArrayBuffer, GlBufferUsage::DynamicDraw>(16);

  glyph_array_.VertexAttribPointer(0, 4, glyph_buffer_);

  glyphs_ = GlGlyphs(GetEngine()->LoadFont("consola"));

  // Ui rendering
  ui_program_.Attach(GlShader("..\\src\\shader\\ui.vert"));
  ui_program_.Attach(GlShader("..\\src\\shader\\ui.frag"));
  ui_program_.Link();

  // 1024 floats
  ui_buffer_ = decltype(ui_buffer_)(1024);

  ui_array_.VertexAttribPointer(0, 2, ui_buffer_);

  splitview_->Initialize();
  treeview_->Initialize();
  viewer_->Initialize();
}

void Painter::SetViewport()
{
  glViewport(0, 0, Width(), Height());
}

void Painter::SetViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);
}

void Painter::Display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  splitview_->Move(0., 0.);
  splitview_->Resize(Width(), Height());
  splitview_->SetScreenPosition(0., 0.);
  splitview_->Draw();
}

void Painter::RenderText(const std::wstring& s, float x, float y, float font_size, const Vector3f& color)
{
  SetViewport();

  auto w = static_cast<float>(Width());
  auto h = static_cast<float>(Height());
  Eigen::Matrix4f font_projection;
  font_projection.setZero();
  font_projection(0, 0) = 2.f / w;
  font_projection(1, 1) = 2.f / h;
  font_projection(2, 2) = 1.f;
  font_projection(0, 3) = -1.;
  font_projection(1, 3) = -1.;
  font_projection(3, 3) = 1.f;

  text_program_.Use();
  text_program_.UniformMatrix4f("projection", font_projection);

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
    float ypos = h - 128.f * font_size - y - (glyph_size.height - glyph_size.bearing_y) * font_size;

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

void Painter::DrawRect(float xmin, float ymin, float xmax, float ymax, const Vector4f& color)
{
  SetViewport();

  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  ui_program_.Use();
  ui_program_.Uniform4f("monitor", 0.f, 0.f, static_cast<float>(Width()), static_cast<float>(Height()));
  ui_program_.Uniform4f("color", color);

  std::vector<float> buffer {
    xmin, ymin,
    xmin, ymax,
    xmax, ymin,
    xmax, ymax,
  };

  ui_buffer_.BufferSubData(buffer);

  ui_array_.DrawArrays(GlVertexArray::DrawType::TriangleStrip, 4);
}
}
