#ifndef SOFTPHYS_VIEWER_SHADER_GL_PROGRAM_H_
#define SOFTPHYS_VIEWER_SHADER_GL_PROGRAM_H_

#include <glad/glad.h>
#include <Eigen/Dense>

#include "softphys/viewer/shader/gl_shader.h"
#include "softphys/data/eigen.h"
#include "softphys/viewer/camera.h"
#include "softphys/viewer/light.h"

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

  void Attach(GlShader&& shader);
  void Link();

  void Use();
  void Stop();

  // Gl uniform functions
  // Prerequisites: Caller should call Use() beforehand.
  void Uniform3f(const std::string& name, float v0, float v1, float v2);
  void Uniform3f(const std::string& name, const Vector3f& v);
  void Uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void Uniform4f(const std::string& name, const Vector4f& v);
  void Uniform1i(const std::string& name, int i);
  void Uniform1f(const std::string& name, float v);
  void Uniform2f(const std::string& name, float v0, float f1);
  void UniformMatrix4f(const std::string& name, const Eigen::Matrix4f& m);

  // Preset 
  // Side effects: Callee calls Use() when the function is called.
  void SetCamera(const Camera& camera);
  void SetLights(const std::vector<Light>& lights);

private:
  bool is_created_;

  GLuint id_;

  std::vector<GlShader> shaders_;
};
}

#endif // SOFTPHYS_VIEWER_SHADER_GL_PROGRAM_H_
