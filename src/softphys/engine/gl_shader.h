#ifndef SOFTPHYS_ENGINE_GL_SHADER_H_
#define SOFTPHYS_ENGINE_GL_SHADER_H_

#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

namespace softphys
{
enum class GlShaderType
{
  VertexShader,
  FragmentShader
};

class GlShaderBase
{
public:
  enum class LoadStatus
  {
    Successful,
    Failed,
  };

public:
  GlShaderBase()
    : id_(0), load_status_(LoadStatus::Failed)
  {
  };

  virtual ~GlShaderBase()
  {
    if (load_status_ == LoadStatus::Successful)
      glDeleteShader(id_);
  }

  GlShaderBase(const GlShaderBase& rhs) = delete;
  GlShaderBase& operator = (const GlShaderBase& rhs) = delete;

  GlShaderBase(GlShaderBase&& rhs) noexcept
  {
    id_ = rhs.id_;
    load_status_ = rhs.load_status_;
    rhs.load_status_ = LoadStatus::Failed;
  }

  GlShaderBase& operator = (GlShaderBase&& rhs) noexcept
  {
    id_ = rhs.id_;
    load_status_ = rhs.load_status_;
    rhs.load_status_ = LoadStatus::Failed;
    return *this;
  }

  auto Id() const
  {
    return id_;
  }

protected:
  static constexpr GLenum ShaderTypeToGlEnum(GlShaderType type)
  {
    switch (type)
    {
    case GlShaderType::VertexShader:
      return GL_VERTEX_SHADER;
    case GlShaderType::FragmentShader:
      return GL_FRAGMENT_SHADER;
    default:
      return 0;
    }
  }

  GLuint id_;
  LoadStatus load_status_;
};

template<GlShaderType type>
class GlShader : public GlShaderBase
{
public:
  GlShader() = delete;

  explicit GlShader(std::string&& filename)
    : GlShaderBase()
  {
    std::ifstream fin(filename);
    if (!fin.is_open())
      return;

    std::stringstream ss;
    ss << fin.rdbuf();
    std::string source = ss.str();

    fin.close();

    id_ = glCreateShader(ShaderTypeToGlEnum(type));

    const char* source_ptr = source.data();
    glShaderSource(id_, 1, &source_ptr, NULL);

    glCompileShader(id_);

    GLint is_compiled = 0;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
      GLint max_length = 0;
      glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<GLchar> error_log(max_length);
      glGetShaderInfoLog(id_, max_length, &max_length, error_log.data());

      load_status_ = LoadStatus::Failed;
      glDeleteShader(id_);

      return;
    }

    load_status_ = LoadStatus::Successful;
  }

  ~GlShader()
  {
  }

  GlShader(const GlShader& rhs) = delete;
  GlShader& operator = (const GlShader& rhs) = delete;

  GlShader(GlShader&& rhs) = default;
  GlShader& operator = (GlShader&& rhs) = default;

private:
};

using GlVertexShader = GlShader<GlShaderType::VertexShader>;
using GlFragmentShader = GlShader<GlShaderType::FragmentShader>;
}

#endif // SOFTPHYS_ENGINE_GL_SHADER_H_
