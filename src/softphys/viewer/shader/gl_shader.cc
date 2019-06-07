#include "softphys/viewer/shader/gl_shader.h"

namespace softphys
{
GlShader::GlShader(Type type)
  : type_(type), id_(0), load_status_(LoadStatus::Failed)
{
}

GlShader::~GlShader()
{
  if (load_status_ == LoadStatus::Successful)
    glDeleteShader(id_);
}

GlShader::GlShader(const std::string& filename)
{
  // Infer the type of shader from the extension of file
  auto extension_location = filename.find_last_of('.');
  if (extension_location == std::string::npos)
    throw std::runtime_error("GlShader class cannot infer shader type (vertex, fragment, etc.) without the extension on the filename.");

  if (filename.substr(extension_location) == ".vert")
  {
    type_ = Type::VertexShader;
    LoadFromFile(filename);
  }
  else if (filename.substr(extension_location) == ".frag")
  {
    type_ = Type::FragmentShader;
    LoadFromFile(filename);
  }
  else
    throw std::runtime_error("GlShader class cannot infer shader type (vertex, fragment, etc.) with an unknown extension on the filename.");
}

GlShader::GlShader(Type type, const std::string& filename)
  : type_(type)
{
  LoadFromFile(filename);
}

void GlShader::LoadFromFile(const std::string& filename)
{
  std::ifstream fin(filename);
  if (!fin.is_open())
    return;

  std::stringstream ss;
  ss << fin.rdbuf();
  std::string source = ss.str();

  fin.close();

  id_ = glCreateShader(ShaderTypeToGlEnum(type_));

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
}
