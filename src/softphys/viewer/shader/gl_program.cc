#include "softphys/viewer/shader/gl_program.h"

#include "softphys/scene/scene.h"

namespace softphys
{
GlProgram::GlProgram()
  : is_created_(false), id_(0)
{
}

GlProgram::~GlProgram()
{
  if (is_created_)
    glDeleteProgram(id_);
}

GlProgram::GlProgram(GlProgram&& rhs) noexcept
{
  id_ = rhs.id_;
  is_created_ = rhs.is_created_;
  rhs.is_created_ = false;
}

GlProgram& GlProgram::operator = (GlProgram&& rhs) noexcept
{
  id_ = rhs.id_;
  is_created_ = rhs.is_created_;
  rhs.is_created_ = false;
  return *this;
}

void GlProgram::Attach(GlShader&& shader)
{
  shaders_.push_back(std::move(shader));
}

void GlProgram::Link()
{
  id_ = glCreateProgram();

  for (const auto& shader : shaders_)
    glAttachShader(id_, shader.Id());

  glLinkProgram(id_);

  GLint is_linked = 0;
  glGetProgramiv(id_, GL_LINK_STATUS, &is_linked);
  if (!is_linked)
  {
    GLint max_length = 0;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(id_, max_length, &max_length, info_log.data());

    is_created_ = false;
    glDeleteProgram(id_);
    shaders_.clear();

    return;
  }

  for (const auto& shader : shaders_)
    glDetachShader(id_, shader.Id());

  is_created_ = true;
}

void GlProgram::Use()
{
  glUseProgram(id_);
}

void GlProgram::Stop()
{
  glUseProgram(0);
}

void GlProgram::Uniform3f(const std::string& name, float v0, float v1, float v2)
{
  glUniform3f(glGetUniformLocation(id_, name.c_str()), v0, v1, v2);
}

void GlProgram::Uniform3f(const std::string& name, const Vector3f& v)
{
  glUniform3f(glGetUniformLocation(id_, name.c_str()), v(0), v(1), v(2));
}

void GlProgram::Uniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
  glUniform4f(glGetUniformLocation(id_, name.c_str()), v0, v1, v2, v3);
}

void GlProgram::Uniform4f(const std::string& name, const Vector4f& v)
{
  glUniform4f(glGetUniformLocation(id_, name.c_str()), v(0), v(1), v(2), v(3));
}

void GlProgram::Uniform1i(const std::string& name, int i)
{
  glUniform1i(glGetUniformLocation(id_, name.c_str()), i);
}

void GlProgram::Uniform1f(const std::string& name, float v)
{
  glUniform1f(glGetUniformLocation(id_, name.c_str()), v);
}

void GlProgram::Uniform2f(const std::string& name, float v0, float v1)
{
  glUniform2f(glGetUniformLocation(id_, name.c_str()), v0, v1);
}

void GlProgram::UniformMatrix4f(const std::string& name, const Eigen::Matrix4f& m)
{
  glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, m.data());
}

void GlProgram::SetCamera(const Camera& camera)
{
  Use();

  UniformMatrix4f("projection", camera.Projectionf());
  UniformMatrix4f("view", camera.Viewf());
  Uniform3f("eye", camera.GetEye().cast<float>());
}

void GlProgram::SetLights(const std::vector<Light>& lights)
{
  Use();

  for (int i = 0; i < lights.size() && i < scene::Scene::max_lights; i++)
  {
    const auto& light = lights[i];

    std::string name = "lights[" + std::to_string(i) + "]";
    Uniform1i(name + ".use", 1);

    switch (light.type)
    {
    case Light::Type::Directional:
      Uniform1i(name + ".type", 0);
      Uniform3f(name + ".position", light.position.normalized());
      break;
    case Light::Type::Point:
      Uniform1i(name + ".type", 1);
      Uniform3f(name + ".position", light.position);
      break;
    default:
      Uniform1i(name + ".type", 2);
      break;
    }

    Uniform3f(name + ".ambient", light.ambient);
    Uniform3f(name + ".diffuse", light.diffuse);
    Uniform3f(name + ".specular", light.specular);
  }
  for (int i = lights.size(); i < scene::Scene::max_lights; i++)
    Uniform1i("lights[" + std::to_string(i) + "].use", 0);
}
}
