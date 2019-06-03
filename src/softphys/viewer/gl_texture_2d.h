#ifndef SOFTPHYS_VIEWER_GL_TEXTURE_2D_H_
#define SOFTPHYS_VIEWER_GL_TEXTURE_2D_H_

#include "softphys/viewer/gl_texture.h"

namespace softphys
{
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

#endif // SOFTPHYS_VIEWER_GL_TEXTURE_2D_H_
