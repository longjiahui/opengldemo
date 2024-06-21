#include "gl/texture.hpp"
#include "lib/glfw.hpp"

using namespace std;
using namespace huigl;

void Texture::use() { glBindTexture(GL_TEXTURE_2D, this->instance); }

Texture::Texture(Image const &image, GLenum colorMode) {
  glGenTextures(1, &this->instance);
  this->use();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0,
               colorMode, GL_UNSIGNED_BYTE, image.data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() { glDeleteTextures(1, &this->instance); }

shared_ptr<Texture> Texture::fromFile(const char *p, GLenum colorMode) {
  return make_shared<Texture>(
      *Image::fromFile(p, colorMode == GL_RGBA ? STBI_rgb_alpha : STBI_rgb),
      colorMode);
}
