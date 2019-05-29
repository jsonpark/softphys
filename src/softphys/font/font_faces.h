#ifndef SOFTPHYS_FONT_FONT_FACES_H_
#define SOFTPHYS_FONT_FONT_FACES_H_

#include <map>
#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "softphys/font/font_face.h"

namespace softphys
{
class FontFaces
{
public:
  FontFaces();
  ~FontFaces();

  FontFace& Load(const std::string& font);

  auto Library() const
  {
    return &ft_library_;
  }

private:
  FT_Library ft_library_;

  std::map<std::string, FontFace> font_faces_;
};
}

#endif // SOFTPHYS_FONT_FONT_FACES_H_
