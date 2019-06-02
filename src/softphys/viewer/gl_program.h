#ifndef SOFTPHYS_VIEWER_GL_PROGRAM_H_
#define SOFTPHYS_VIEWER_GL_PROGRAM_H_

#include <glad/glad.h>
#include <Eigen/Dense>

#include "softphys/viewer/gl_shader.h"
#include "softphys/data/eigen.h"

namespace softphys
{
class GlProgram
{
public:
  enum class LoadStatus
  {
    Successful,
    Failed,
  };

public:
  GlProgram();
  ~GlProgram();

  GlProgram(const GlProgram& rhs) = delete;
  GlProgram& operator = (const GlProgram& rhs) = delete;

  GlProgram(GlProgram&& rhs) noexcept;
  GlProgram& operator = (GlProgram&& rhs) noexcept;

  void Attach(GlShaderBase&& shader);
  void Link();

  void Use();
  void Stop();

  void Uniform3f(const std::string& name, float v0, float v1, float v2);
  void Uniform3f(const std::string& name, const Vector3f& v);
  void Uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void Uniform4f(const std::string& name, const Vector4f& v);
  void Uniform1i(const std::string& name, int i);
  void Uniform1f(const std::string& name, float v);
  void UniformMatrix4f(const std::string& name, const Eigen::Matrix4f& m);

private:
  bool is_created_;

  GLuint id_;

  std::vector<GlShaderBase> shaders_;
};
}

#endif // SOFTPHYS_VIEWER_GL_PROGRAM_H_
