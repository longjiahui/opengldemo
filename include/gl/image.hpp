#pragma once

#include <memory>

#include "lib/stb_image.hpp"

namespace huigl {

class Image {
private:
  void setImage(unsigned char *, const unsigned int &, const unsigned int &);

public:
  unsigned char *data;
  unsigned int width;
  unsigned int height;
  static std::shared_ptr<Image> fromFile(const char *, int = STBI_default);
  Image();
  Image(unsigned char *data, unsigned int width, unsigned int height);

  /* 不允许拷贝构造 / 赋值构造 / 转移 */
  Image(Image &&) = delete;
  Image(Image &) = delete;
  Image &operator=(Image &) = delete;
  Image &operator=(Image &&) = delete;

  ~Image();
};
} // namespace huigl
