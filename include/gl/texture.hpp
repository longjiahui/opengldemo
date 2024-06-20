#pragma once

#include "image.hpp"

#include "lib/glfw.hpp"

#include <memory>

namespace huigl {

class Texture {
public:
  static std::shared_ptr<Texture> fromFile(const char *, GLenum = GL_RGB);
  Texture(const Image &, GLenum = GL_RGB);
  ~Texture();
  void use();

  /* 不允许拷贝构造、赋值、转移 */
  Texture(Texture &&) = delete;
  Texture(Texture &) = delete;
  Texture &operator=(Texture &) = delete;
  Texture &operator=(Texture &&) = delete;

private:
  unsigned int instance;
};
} // namespace huigl