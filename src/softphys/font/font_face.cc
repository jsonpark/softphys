#include "softphys/font/font_face.h"

#include <iostream>

#include "softphys/font/font_faces.h"
#include "softphys/font/glyph.h"
#include "softphys/engine/texture.h"

namespace softphys
{
FontFace::FontFace(FontFaces* ft, const std::string& font)
  : ft_(ft), is_constructed_(false), glyphs_(num_glyphs_)
{
  auto error = FT_New_Face(*ft->Library(), (std::string("C:\\Windows\\Fonts\\") + font + ".ttc").c_str(), 0, &face_);
  if (error == FT_Err_Unknown_File_Format)
  {
    std::cout << "FreeType: The font file could be openedand read, but it appears that its font format is unsupported." << std::endl;
  }
  else if (error)
  {
    std::cout << "FreeType: The font file could not be opened or read, or that it is broken." << std::endl;
  }

  is_constructed_ = true;

  FT_Select_Charmap(face_, FT_ENCODING_UNICODE);
  FT_Set_Pixel_Sizes(face_, 0, 128);
}

FontFace::~FontFace()
{
  if (is_constructed_)
    FT_Done_Face(face_);
}

FontFace::FontFace(FontFace&& rhs)
  : ft_(rhs.ft_), is_constructed_(rhs.is_constructed_), face_(rhs.face_), glyphs_(std::move(rhs.glyphs_))
{
  rhs.is_constructed_ = false;
}

const Glyph& FontFace::operator[] (wchar_t c)
{
  if (!glyphs_[c].IsGenerated())
  {
    // Load character glyph 
    if (FT_Load_Char(face_, c, FT_LOAD_RENDER))
    {
      std::cout << "FreeType: Failed to load glyplh." << std::endl;
    }

    // Generate texture
    Texture<TextureFormat::RED> texture(face_->glyph->bitmap.width, face_->glyph->bitmap.rows, face_->glyph->bitmap.buffer);
    glyphs_[c] = Glyph(std::move(texture), face_->glyph->bitmap.width, face_->glyph->bitmap.rows, face_->glyph->bitmap_left, face_->glyph->bitmap_top, face_->glyph->advance.x);
  }

  return glyphs_[c];
}
}
