#include "softphys/font/font_faces.h"

#include <iostream>

namespace softphys
{
FontFaces::FontFaces()
{
  auto error = FT_Init_FreeType(&ft_library_);
  if (error)
  {
    std::cout << "FreeType: An error occurred during library initialization" << std::endl;
  }
}

FontFaces::~FontFaces()
{
  // TODO: destroy library
}

FontFace& FontFaces::Load(const std::string& font)
{
  auto it = font_faces_.find(font);
  if (it == font_faces_.cend())
  {
    auto p = font_faces_.emplace(font, FontFace(this, font));
    return p.first->second;
  }

  return it->second;
}
}
