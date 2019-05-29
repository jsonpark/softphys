#ifndef SOFTPHYS_VIEWER_GL_VERTEX_ARRAY_H_
#define SOFTPHYS_VIEWER_GL_VERTEX_ARRAY_H_

#include <glad/glad.h>

#include "softphys/viewer/gl_buffer.h"

namespace softphys
{
class GlVertexArray
{
public:
  enum class DrawType
  {
    Triangles,
    TriangleStrip,
    Lines,
  };

private:
  static constexpr GLenum DrawTypeToGlEnum(DrawType type)
  {
    switch (type)
    {
    case DrawType::Triangles:
      return GL_TRIANGLES;
    case DrawType::TriangleStrip:
      return GL_TRIANGLE_STRIP;
    case DrawType::Lines:
      return GL_LINES;
    default:
      return 0;
    }
  }

public:
  GlVertexArray();
  ~GlVertexArray();

  GlVertexArray(const GlVertexArray& rhs) = delete;
  GlVertexArray& operator = (const GlVertexArray& rhs) = delete;

  GlVertexArray(GlVertexArray&& rhs) = default;
  GlVertexArray& operator = (GlVertexArray&& rhs) = default;

  template<typename T, GlBufferTarget target, GlBufferUsage usage>
  void VertexAttribPointer(int index, int size, const GlBuffer<T, target, usage>& buffer, int stride = 0, int offset = 0)
  {
    Bind();
    buffer.Bind();
    glVertexAttribPointer(index, size, buffer.GlDataType(), GL_FALSE, stride * sizeof(T), (GLvoid*)(offset * sizeof(T)));
    glEnableVertexAttribArray(index);
    Unbind();
    buffer.Unbind();
  }

  template<typename T, GlBufferTarget target, GlBufferUsage usage>
  void DrawElements(DrawType type, const GlBuffer<T, target, usage>& element_buffer, int count = element_buffer.NumElements(), int offset = 0)
  {
    Bind();
    element_buffer.Bind();
    glDrawElements(DrawTypeToGlEnum(type), count, BaseTypeToGlEnum<T>(), (void*)offset);
    Unbind();
    element_buffer.Unbind();
  }

  void DrawArrays(DrawType type, int count, int offset = 0)
  {
    Bind();
    glDrawArrays(DrawTypeToGlEnum(type), offset, count);
    Unbind();
  }

  void Bind();
  void Unbind();

private:
  GLuint id_;
};
}

#endif // SOFTPHYS_VIEWER_GL_VERTEX_ARRAY_H_
