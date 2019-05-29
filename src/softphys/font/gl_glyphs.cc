#include "softphys/font/gl_glyphs.h"

namespace softphys
{
GlGlyphs::GlGlyphs()
  : face_(nullptr), cache_size_(0)
{
}

GlGlyphs::GlGlyphs(FontFace& face, int cache_size)
  : face_(&face), cache_size_(cache_size),
  glyph_sizes_(num_glyphs_), textures_(num_glyphs_), is_glyph_loaded_(num_glyphs_, false)
{
}

GlGlyphs::TextureType& GlGlyphs::GetTexture(wchar_t c)
{
  Load(c);
  return textures_[c];
}

Glyph::Size& GlGlyphs::GetGlyphSize(wchar_t c)
{
  Load(c);
  return glyph_sizes_[c];
}

void GlGlyphs::Load(wchar_t c)
{
  // TODO: if the number of loaded glyphs exceeds cache size, unload the oldest glyphs

  if (!is_glyph_loaded_[c])
  {
    const auto& face_character = face_->operator[](c);
    glyph_sizes_[c] = face_character.GetSize();
    textures_[c] = TextureType(face_character.Texture());
    textures_[c].Bind();
    textures_[c].WrapS(GlTextureWrapping::ClampToEdge);
    textures_[c].WrapT(GlTextureWrapping::ClampToEdge);
    textures_[c].MinFilter(GlTextureFilter::LinearMipmapLinear);
    textures_[c].MagFilter(GlTextureFilter::Linear);
    textures_[c].Unbind();
    is_glyph_loaded_[c] = true;
  }
}
}
