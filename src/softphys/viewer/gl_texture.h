#ifndef SOFTPHYS_VIEWER_GL_TEXTURE_H_
#define SOFTPHYS_VIEWER_GL_TEXTURE_H_

#include <glad/glad.h>

#include "softphys/data/texture.h"

namespace softphys
{
enum class GlTextureType
{
  Texture2D,
  TextureCubeMap
};

constexpr GLuint TextureTypeToGlEnum(GlTextureType type) noexcept
{
  switch (type)
  {
  case GlTextureType::Texture2D:
    return GL_TEXTURE_2D;
  case GlTextureType::TextureCubeMap:
    return GL_TEXTURE_CUBE_MAP;
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
}

#endif // SOFTPHYS_VIEWER_GL_TEXTURE_H_
