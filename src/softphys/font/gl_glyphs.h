#ifndef SOFTPHYS_FONT_GL_GLYPHS_H_
#define SOFTPHYS_FONT_GL_GLYPHS_H_

#include <string>

#include "softphys/font/font_face.h"
#include "softphys/font/glyph.h"
#include "softphys/viewer/gl_texture_2d.h"

namespace softphys
{
class GlGlyphs
{
private:
  static const int num_glyphs_ = 65536;
  using TextureType = GlTexture2D;

public:
  GlGlyphs();

  GlGlyphs(FontFace& face, int cache_size = 1024);

  ~GlGlyphs() = default;

  GlGlyphs(GlGlyphs&& rhs)
    : face_(rhs.face_), cache_size_(rhs.cache_size_),
    is_glyph_loaded_(std::move(rhs.is_glyph_loaded_)),
    textures_(std::move(rhs.textures_)),
    glyph_sizes_(std::move(rhs.glyph_sizes_))
  {
  }

  GlGlyphs& operator = (GlGlyphs&& rhs)
  {
    face_ = rhs.face_;
    cache_size_ = rhs.cache_size_;

    is_glyph_loaded_ = std::move(rhs.is_glyph_loaded_);
    textures_ = std::move(rhs.textures_);
    glyph_sizes_ = std::move(rhs.glyph_sizes_);

    return *this;
  }

  TextureType& GetTexture(wchar_t c);
  Glyph::Size& GetGlyphSize(wchar_t c);

private:
  void Load(wchar_t c);

  FontFace* face_;
  int cache_size_;

  std::vector<bool> is_glyph_loaded_;
  std::vector<TextureType> textures_;
  std::vector<Glyph::Size> glyph_sizes_;
};
}

#endif // SOFTPHYS_FONT_GL_GLYPHS_H_
