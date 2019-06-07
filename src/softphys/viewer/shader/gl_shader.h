#ifndef SOFTPHYS_VIEWER_SHADER_GL_SHADER_H_
#define SOFTPHYS_VIEWER_SHADER_GL_SHADER_H_

#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

namespace softphys
{
class GlShader
{
public:
  enum class Type
  {
    VertexShader,
    FragmentShader,
    Undefined
  };

  enum class LoadStatus
  {
    Successful,
    Failed,
  };

protected:
  static constexpr GLenum ShaderTypeToGlEnum(Type type)
  {
    switch (type)
    {
    case Type::VertexShader:
      return GL_VERTEX_SHADER;
    case Type::FragmentShader:
      return GL_FRAGMENT_SHADER;
    default:
      return 0;
    }
  }
public:
  GlShader() = delete;
  GlShader(Type type);
  GlShader(const std::string& filename);
  GlShader(Type type, const std::string& filename);

  virtual ~GlShader();

  GlShader(const GlShader& rhs) = delete;
  GlShader& operator = (const GlShader& rhs) = delete;

  GlShader(GlShader&& rhs) noexcept
  {
    id_ = rhs.id_;
    load_status_ = rhs.load_status_;
    rhs.load_status_ = LoadStatus::Failed;
  }

  GlShader& operator = (GlShader&& rhs) noexcept
  {
    id_ = rhs.id_;
    load_status_ = rhs.load_status_;
    rhs.load_status_ = LoadStatus::Failed;
    return *this;
  }

  void LoadFromFile(const std::string& filename);

  auto Id() const
  {
    return id_;
  }

  Type type_ = Type::Undefined;
  GLuint id_;
  LoadStatus load_status_;
};
}

#endif // SOFTPHYS_VIEWER_SHADER_GL_SHADER_H_
