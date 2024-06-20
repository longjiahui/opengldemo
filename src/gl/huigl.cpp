#include "gl/huigl.hpp"
#include "lib/glfw.hpp"
#include "lib/stb_image.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace huigl;
using namespace std;

VAO::VAO() { glGenVertexArrays(1, &(this->instance)); }
VAO::~VAO() { glDeleteVertexArrays(1, &this->instance); }

shared_ptr<VBO> VAO::createVBO(shared_ptr<vector<float>> vertices) {
  return make_shared<VBO>(vertices);
}
void VAO::use() { glBindVertexArray(this->instance); }
void VAO::use(VAOUseFunc func) const {
  glBindVertexArray(this->instance);
  func();
}
void VAO::useVBO(const VBO &vbo, const std::vector<VBOUsage> &usages) {
  GLint totalLength = 0;
  for (auto usage : usages) {
    totalLength += usage.length;
  }
  this->use([&vbo, &usages, &totalLength]() {
    vbo.use();
    for (auto usage : usages) {
      glVertexAttribPointer(usage.index, usage.length, GL_FLOAT, GL_FALSE,
                            totalLength * sizeof(float),
                            (void *)(usage.offset * sizeof(float)));
      glEnableVertexAttribArray(usage.index);
    }
  });
}

void VAO::drawArray(shared_ptr<Program> program, GLsizei size, GLint offset,
                    GLenum mode) {
  this->use([&]() {
    program->use();
    glDrawArrays(mode, offset, size);
  });
}

VBO::VBO(std::shared_ptr<std::vector<float>> vertices, GLenum usage) {
  glGenBuffers(1, &this->instance);
  this->use();
  glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float),
               vertices->data(), GL_STATIC_DRAW);
}

void VBO::use() const { glBindBuffer(GL_ARRAY_BUFFER, this->instance); }

VBO::~VBO() { glDeleteBuffers(1, &this->instance); }

void Image::setImage(unsigned char *data, const unsigned int &width,
                     const unsigned int &height) {
  this->data = data;
  this->width = width;
  this->height = height;
}

shared_ptr<Image> Image::load(const char *path) {
  int width, height, channels;
  return make_shared<Image>(stbi_load(path, &width, &height, &channels, 0),
                            width, height);
}

Image::Image(unsigned char *data, unsigned int width, unsigned int height) {
  this->setImage(data, width, height);
}

Image::Image(Image &&image) {
  this->data = image.data;
  this->width = image.width;
  this->height = image.height;
  image.data = nullptr;
  image.width = 0;
  image.height = 0;
}

Image::~Image() { stbi_image_free(this->data); }

void Texture::use() { glBindTexture(GL_TEXTURE_2D, this->instance); }

Texture::Texture(const Image &image) {
  glGenTextures(1, &this->instance);
  this->use();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image.data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() { glDeleteTextures(1, &this->instance); }