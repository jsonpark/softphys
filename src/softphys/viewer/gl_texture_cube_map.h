#ifndef SOFTPHYS_VIEWER_GL_TEXTURE_CUBE_MAP_H_
#define SOFTPHYS_VIEWER_GL_TEXTURE_CUBE_MAP_H_

#include "softphys/viewer/gl_texture.h"

namespace softphys
{
class GlTextureCubeMap
{
public:
  GlTextureCubeMap()
    : is_generated_(false), id_(0)
  {
  }

  template<TextureFormat format>
  explicit GlTextureCubeMap(const std::vector<std::shared_ptr<Texture<format>>>& texture)
    : is_generated_(true), id_(0)
  {
    glGenTextures(1, &id_);
    Bind();
    for (int i = 0; i < 6; i++)
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texture[i]->InternalFormatGlEnum(), texture[i]->Width(), texture[i]->Height(), 0, texture[i]->FormatGlEnum(), GL_UNSIGNED_BYTE, texture[i]->Data());
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    WrapS(GlTextureWrapping::ClampToEdge);
    WrapT(GlTextureWrapping::ClampToEdge);
    WrapR(GlTextureWrapping::ClampToEdge);
    MinFilter(GlTextureFilter::Linear);
    MagFilter(GlTextureFilter::Linear);
    Unbind();
  }

  ~GlTextureCubeMap()
  {
    if (is_generated_)
      glDeleteProgram(id_);
  }

  GlTextureCubeMap(const GlTextureCubeMap& rhs) = delete;
  GlTextureCubeMap& operator = (const GlTextureCubeMap& rhs) = delete;

  GlTextureCubeMap(GlTextureCubeMap&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_generated_ = rhs.is_generated_;
    rhs.is_generated_ = false;
  }

  GlTextureCubeMap& operator = (GlTextureCubeMap&& rhs) noexcept
  {
    id_ = rhs.id_;
    is_generated_ = rhs.is_generated_;
    rhs.is_generated_ = false;
    return *this;
  }

  void Bind()
  {
    if (is_generated_)
      glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
  }

  void Bind(int active_texture)
  {
    if (is_generated_)
    {
      glActiveTexture(GL_TEXTURE0 + active_texture);
      glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
      glActiveTexture(GL_TEXTURE0);
    }
  }

  void Unbind()
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  }

  void WrapS(GlTextureWrapping wrap)
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, TextureWrappingToGlEnum(wrap));
  }

  void WrapT(GlTextureWrapping wrap)
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, TextureWrappingToGlEnum(wrap));
  }

  void WrapR(GlTextureWrapping wrap)
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, TextureWrappingToGlEnum(wrap));
  }

  void MinFilter(GlTextureFilter filter)
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, TextureFilterToGlEnum(filter));
  }

  void MagFilter(GlTextureFilter filter)
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, TextureFilterToGlEnum(filter));
  }

private:
  bool is_generated_;
  GLuint id_;
};
}

#endif // SOFTPHYS_VIEWER_GL_TEXTURE_CUBE_MAP_H_
