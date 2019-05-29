#ifndef SOFTPHYS_FONT_GLYPH_H_
#define SOFTPHYS_FONT_GLYPH_H_

#include <string>

#include "softphys/data/texture.h"

namespace softphys
{
class Glyph
{
public:
  struct Size
  {
    int width = 0;
    int height = 0;
    int bearing_x = 0;
    int bearing_y = 0;
    unsigned int advance = 0u;
  };

public:
  Glyph();

  Glyph(Texture<TextureFormat::RED>&& texture, int width, int height, int bearing_x, int bearing_y, unsigned int advance);

  Glyph(const Glyph& rhs) = default;
  Glyph& operator = (const Glyph& rhs) = default;

  Glyph(Glyph&& rhs)
  {
    if (rhs.is_generated_)
    {
      is_generated_ = rhs.is_generated_;
      size_ = rhs.size_;
      texture_ = std::move(rhs.texture_);

      rhs.is_generated_ = false;
    }

    else
      is_generated_ = false;
  }

  Glyph& operator = (Glyph&& rhs)
  {
    if (rhs.is_generated_)
    {
      is_generated_ = rhs.is_generated_;
      size_ = rhs.size_;
      texture_ = std::move(rhs.texture_);

      rhs.is_generated_ = false;
    }

    else
      is_generated_ = false;

    return *this;
  }

  const auto& GetSize() const noexcept
  {
    return size_;
  }

  bool IsGenerated() const noexcept
  {
    return is_generated_;
  }

  const auto& Texture() const noexcept
  {
    return texture_;
  }

  auto Width() const noexcept
  {
    return size_.width;
  }

  auto Height() const noexcept
  {
    return size_.height;
  }

  auto BearingX() const noexcept
  {
    return size_.bearing_x;
  }

  auto BearingY() const noexcept
  {
    return size_.bearing_y;
  }

  auto Advance() const noexcept
  {
    return size_.advance;
  }

private:
  bool is_generated_ = false;

  softphys::Texture<TextureFormat::RED> texture_;
  Size size_;
};
}

#endif // SOFTPHYS_FONT_GLYPH_H_
