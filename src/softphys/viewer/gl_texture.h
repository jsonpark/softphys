#ifndef SOFTPHYS_VIEWER_GL_TEXTURE_H_
#define SOFTPHYS_VIEWER_GL_TEXTURE_H_

#include <glad/glad.h>

#include "softphys/data/texture.h"

namespace softphys
{
enum class GlTextureType
{
  Texture2D,
};

constexpr GLuint TextureTypeToGlEnum(GlTextureType type) noexcept
{
  switch (type)
  {
  case GlTextureType::Texture2D:
    return GL_TEXTURE_2D;
  default:
    return 0;
  }
}


enum class GlTextureWrapping
{
  Repeat,
  MirroredRepeat,
  ClampToEdge,
  ClampToBorder,
};

constexpr GLuint TextureWrappingToGlEnum(GlTextureWrapping wrapping) noexcept
{
  switch (wrapping)
  {
  case GlTextureWrapping::Repeat:
    return GL_REPEAT;
  case GlTextureWrapping::MirroredRepeat:
    return GL_MIRRORED_REPEAT;
  case GlTextureWrapping::ClampToEdge:
    return GL_CLAMP_TO_EDGE;
  case GlTextureWrapping::ClampToBorder:
    return GL_CLAMP_TO_BORDER;
  default:
    return 0;
  }
}


enum class GlTextureFilter
{
  Nearest,
  Linear,
  NearestMipmapNearest,
  NearestMipmapLinear,
  LinearMipmapNearest,
  LinearMipmapLinear,
};

constexpr GLuint TextureFilterToGlEnum(GlTextureFilter filter) noexcept
{
  switch (filter)
  {
  case GlTextureFilter::Nearest:
    return GL_NEAREST;
  case GlTextureFilter::Linear:
    return GL_LINEAR;
  case GlTextureFilter::NearestMipmapNearest:
    return GL_NEAREST_MIPMAP_NEAREST;
  case GlTextureFilter::NearestMipmapLinear:
    return GL_NEAREST_MIPMAP_LINEAR;
  case GlTextureFilter::LinearMipmapNearest:
    return GL_LINEAR_MIPMAP_NEAREST;
  case GlTextureFilter::LinearMipmapLinear:
    return GL_LINEAR_MIPMAP_LINEAR;
  default:
    return 0;
  }
}


template <GlTextureType type>
class GlTexture
{
public:
  GlTexture()
    : is_created_(false), id_(0)
  {
  }

  ~GlTexture()
  {
    if (is_created_)
      glDeleteProgram(id_);
  }

  GlTexture(const GlTexture& rhs) = delete;
  GlTexture& operator = (const GlTexture& rhs) = delete;

  GlTexture(GlTexture&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_created_ = rhs.is_created_;
    rhs.is_created_ = false;
  }

  GlTexture& operator = (GlTexture&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_created_ = rhs.is_created_;
    rhs.is_created_ = false;
    return *this;
  }

  void Bind()
  {
    if (is_created_)
      glBindTexture(TextureTypeToGlEnum(type), id_);
  }

  void Unbind()
  {
    glBindTexture(TextureTypeToGlEnum(type), 0);
  }

private:
  bool is_created_;
  GLuint id_;
};


template <>
class GlTexture<GlTextureType::Texture2D>
{
public:
  GlTexture()
    : is_generated_(false), id_(0)
  {
  }

  template<TextureFormat format>
  explicit GlTexture(const Texture<format>& texture)
    : is_generated_(true), id_(0)
  {
    glGenTextures(1, &id_);
    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, texture.InternalFormatGlEnum(), texture.Width(), texture.Height(), 0, texture.FormatGlEnum(), GL_UNSIGNED_BYTE, texture.Data());
    glGenerateMipmap(GL_TEXTURE_2D);
    WrapS(GlTextureWrapping::Repeat);
    WrapT(GlTextureWrapping::Repeat);
    MinFilter(GlTextureFilter::Linear);
    MagFilter(GlTextureFilter::Linear);
    Unbind();
  }

  template<TextureFormat format>
  explicit GlTexture(const Texture<format>& texture, int mipmap_levels)
    : is_generated_(true), id_(0)
  {
    glGenTextures(1, &id_);
    Bind();
    glTexStorage2D(GL_TEXTURE_2D, mipmap_levels, texture.InternalFormatGlEnum(), texture.Width(), texture.Height());
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture.Width(), texture.Height(), texture.FormatGlEnum(), GL_UNSIGNED_BYTE, texture.Data());
    glGenerateMipmap(GL_TEXTURE_2D);
    WrapS(GlTextureWrapping::Repeat);
    WrapT(GlTextureWrapping::Repeat);
    MinFilter(GlTextureFilter::Linear);
    MagFilter(GlTextureFilter::Linear);
    Unbind();
  }

  ~GlTexture()
  {
    if (is_generated_)
      glDeleteProgram(id_);
  }

  GlTexture(const GlTexture& rhs) = delete;
  GlTexture& operator = (const GlTexture& rhs) = delete;

  GlTexture(GlTexture&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_generated_ = rhs.is_generated_;
    rhs.is_generated_ = false;
  }

  GlTexture& operator = (GlTexture&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_generated_ = rhs.is_generated_;
    rhs.is_generated_ = false;
    return *this;
  }

  void Bind()
  {
    if (is_generated_)
      glBindTexture(GL_TEXTURE_2D, id_);
  }

  void Bind(int active_texture)
  {
    if (is_generated_)
    {
      glActiveTexture(GL_TEXTURE0 + active_texture);
      glBindTexture(GL_TEXTURE_2D, id_);
      glActiveTexture(GL_TEXTURE0);
    }
  }

  void Unbind()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void WrapS(GlTextureWrapping wrap)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrappingToGlEnum(wrap));
  }

  void WrapT(GlTextureWrapping wrap)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrappingToGlEnum(wrap));
  }

  void MinFilter(GlTextureFilter filter)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGlEnum(filter));
  }

  void MagFilter(GlTextureFilter filter)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGlEnum(filter));
  }

private:
  bool is_generated_;
  GLuint id_;
};
}

#endif // SOFTPHYS_VIEWER_GL_TEXTURE_H_
