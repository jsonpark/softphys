#ifndef SOFTPHYS_ENGINE_TEXTURE_H_
#define SOFTPHYS_ENGINE_TEXTURE_H_

#include <string>
#include <vector>

#include <glad/glad.h>
#include <lodepng/lodepng.h>

namespace softphys
{
enum class TextureFormat
{
  RED,
  RGBA,
};

template<TextureFormat format = TextureFormat::RGBA>
class Texture
{
private:
  static constexpr int ByteSize(TextureFormat format)
  {
    switch (format)
    {
    case TextureFormat::RED:
      return 1;

    case TextureFormat::RGBA:
      return 4;

    default:
      return 4;
    }
  }

public:
  static constexpr GLenum InternalFormatGlEnum()
  {
    switch (format)
    {
    case TextureFormat::RED:
      return GL_R8;

    case TextureFormat::RGBA:
      return GL_RGBA8;

    default:
      return 0;
    }
  }

  static constexpr GLenum FormatGlEnum()
  {
    switch (format)
    {
    case TextureFormat::RED:
      return GL_RED;

    case TextureFormat::RGBA:
      return GL_RGBA;

    default:
      return 0;
    }
  }

public:
  Texture() = default;

  Texture(const std::string& filename)
    : width_(0), height_(0)
  {
    auto error = lodepng::decode(data_, width_, height_, filename);

    if (error != 0)
    {
      std::cout << "Lodepng error " << error << ": " << lodepng_error_text(error) << std::endl;
      return;
    }
  }

  Texture(int width, int height, const std::vector<unsigned char>& data)
    : width_(width), height_(height), data_(data)
  {
  }

  Texture(int width, int height, std::vector<unsigned char>&& data)
    : width_(width), height_(height), data_(std::move(data))
  {
  }

  Texture(int width, int height, unsigned char* data)
    : width_(width), height_(height), data_(data, data + ByteSize(format) * width * height)
  {
  }

  Texture(int width, int height)
    : width_(width), height_(height), data_(ByteSize(format) * width * height)
  {
  }

  ~Texture() = default;

  auto Width() const
  {
    return width_;
  }

  auto Height() const
  {
    return height_;
  }

  auto Data() const
  {
    return data_.data();
  }

private:
  unsigned int width_ = 0;
  unsigned int height_ = 0;
  std::vector<unsigned char> data_;
};
}

#endif // SOFTPHYS_ENGINE_TEXTURE_H_
