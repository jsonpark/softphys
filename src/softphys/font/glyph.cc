#include "softphys/font/glyph.h"

namespace softphys
{
Glyph::Glyph()
  : is_generated_(false)
{
}

Glyph::Glyph(softphys::Texture<TextureFormat::RED>&& texture, int width, int height, int bearing_x, int bearing_y, unsigned int advance)
  : is_generated_(true), texture_(std::move(texture))
{
  size_.width = width;
  size_.height = height;
  size_.bearing_x = bearing_x;
  size_.bearing_y = bearing_y;
  size_.advance = advance;
}
}
