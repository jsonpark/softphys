#ifndef SOFTPHYS_FONT_FONT_FACE_H_
#define SOFTPHYS_FONT_FONT_FACE_H_

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "softphys/font/glyph.h"

namespace softphys
{
class FontFaces;

class FontFace
{
private:
  static const int num_glyphs_ = 65536;

public:
  FontFace() = delete;
  FontFace(FontFaces* ft, const std::string& font);
  ~FontFace();

  FontFace(const FontFace& rhs) = delete;
  FontFace& operator = (const FontFace& rhs) = delete;
  
  FontFace(FontFace&& rhs);
  FontFace& operator = (FontFace&& rhs) = delete;

  const Glyph& operator[] (wchar_t c);

private:
  FontFaces* const ft_;

  bool is_constructed_;
  FT_Face face_;

  std::vector<Glyph> glyphs_;
};
}

#endif // SOFTPHYS_FONT_FONT_FACE_H_
