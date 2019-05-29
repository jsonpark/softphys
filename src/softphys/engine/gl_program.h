#ifndef SOFTPHYS_ENGINE_GL_PROGRAM_H_
#define SOFTPHYS_ENGINE_GL_PROGRAM_H_

#include <glad/glad.h>
#include <Eigen/Dense>

#include "softphys/engine/gl_shader.h"

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

  void Uniform(const char* name, float v0, float v1, float v2);
  void Uniform(const char* name, float v0, float v1, float v2, float v3);
  void Uniform(const char* name, int i);
  void Uniform(const char* name, const Eigen::Matrix4f& m);

private:
  bool is_created_;

  GLuint id_;

  std::vector<GlShaderBase> shaders_;
};
}

#endif // SOFTPHYS_ENGINE_GL_PROGRAM_H_
