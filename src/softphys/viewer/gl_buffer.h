#ifndef SOFTPHYS_VIEWER_GL_BUFFER_H_
#define SOFTPHYS_VIEWER_GL_BUFFER_H_

#include <vector>

#include <glad/glad.h>

namespace softphys
{
enum class GlBufferTarget
{
  ArrayBuffer,
  ElementArrayBuffer,
};

enum class GlBufferUsage
{
  StaticDraw,
  DynamicDraw,
};


constexpr GLenum TargetToGlEnum(GlBufferTarget target) noexcept
{
  switch (target)
  {
  case GlBufferTarget::ArrayBuffer:
    return GL_ARRAY_BUFFER;
  case GlBufferTarget::ElementArrayBuffer:
    return GL_ELEMENT_ARRAY_BUFFER;
  default:
    return 0;
  }
}


constexpr GLenum UsageToGlEnum(GlBufferUsage usage) noexcept
{
  switch (usage)
  {
  case GlBufferUsage::StaticDraw:
    return GL_STATIC_DRAW;
  case GlBufferUsage::DynamicDraw:
    return GL_DYNAMIC_DRAW;
  default:
    return 0;
  }
}


template<typename T>
constexpr GLenum BaseTypeToGlEnum() noexcept;

template<>
static constexpr GLenum BaseTypeToGlEnum<float>() noexcept
{
  return GL_FLOAT;
}

template<>
static constexpr GLenum BaseTypeToGlEnum<unsigned int>() noexcept
{
  return GL_UNSIGNED_INT;
}


template<typename T, GlBufferTarget target, GlBufferUsage usage,
         typename std::enable_if_t<std::is_arithmetic<T>::value, int> = 0>
class GlBuffer
{
public:
  GlBuffer()
    : is_generated_(false)
  {
  }

  GlBuffer(int num_elements)
    : is_generated_(true), num_elements_(num_elements)
  {
    glGenBuffers(1, &id_);
    Bind();
    glBufferData(TargetToGlEnum(target), num_elements_ * sizeof T, (void*)0, UsageToGlEnum(usage));
    Unbind();
  }

  GlBuffer(const std::vector<T>& data)
    : is_generated_(true), num_elements_(static_cast<int>(data.size()))
  {
    glGenBuffers(1, &id_);
    Bind();
    glBufferData(TargetToGlEnum(target), num_elements_ * sizeof T, (void*)&data[0], UsageToGlEnum(usage));
    Unbind();
  }

  GlBuffer(std::vector<T>&& data)
    : is_generated_(true), num_elements_(static_cast<int>(data.size()))
  {
    glGenBuffers(1, &id_);
    Bind();
    glBufferData(TargetToGlEnum(target), num_elements_ * sizeof T, (void*)&data[0], UsageToGlEnum(usage));
    Unbind();
  }

  ~GlBuffer()
  {
    if (is_generated_)
      glDeleteBuffers(1, &id_);
  }

  GlBuffer(const GlBuffer& rhs) = delete;
  GlBuffer& operator = (const GlBuffer& rhs) = delete;

  GlBuffer(GlBuffer&& rhs)
  {
    is_generated_ = rhs.is_generated_;
    id_ = rhs.id_;
    num_elements_ = rhs.num_elements_;
    rhs.is_generated_ = false;
  }

  GlBuffer& operator = (GlBuffer&& rhs)
  {
    is_generated_ = rhs.is_generated_;
    id_ = rhs.id_;
    num_elements_ = rhs.num_elements_;
    rhs.is_generated_ = false;

    return *this;
  }

  constexpr GLenum GlDataType() const noexcept
  {
    return BaseTypeToGlEnum<T>();
  }

  void Bind() const
  {
    glBindBuffer(TargetToGlEnum(target), id_);
  }

  void Unbind() const
  {
    glBindBuffer(TargetToGlEnum(target), 0);
  }

  auto NumElements() const noexcept
  {
    return num_elements_;
  }

  void BufferSubData(const std::vector<T>& buffer, int offset = 0)
  {
    auto n = std::min(num_elements_ - offset, static_cast<int>(buffer.size()));

    Bind();
    glBufferSubData(TargetToGlEnum(target), offset * sizeof T, n * sizeof T, buffer.data());
    Unbind();
  }

  void BufferSubData(const std::vector<T>& buffer, int offset, int cnt)
  {
    auto n = std::min(num_elements_ - offset, cnt);

    Bind();
    glBufferSubData(TargetToGlEnum(target), offset * sizeof T, n * sizeof T, buffer.data());
    Unbind();
  }

private:
  bool is_generated_;

  GLuint id_;

  int num_elements_;
};
}

#endif // SOFTPHYS_VIEWER_GL_BUFFER_H_
