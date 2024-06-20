#pragma once

#include <memory>
#include <vector>

#include "program.hpp"

#include "lib/glfw.hpp"

namespace huigl {

typedef struct {
  std::string name;
  GLint offset;
  GLint length;
  // GLint step;
} VBOUsage;

class VBO {
private:
  unsigned int instance;

public:
  VBO(const std::vector<float> &data, GLenum = GL_STATIC_DRAW);
  /* 不允许拷贝构造 / 赋值构造 / 转移 */
  VBO(VBO &&) = delete;
  VBO(VBO &) = delete;
  VBO &operator=(VBO &) = delete;
  VBO &operator=(VBO &&) = delete;

  ~VBO();

  void use() const;
};

class EBO {
private:
  unsigned int instance;

public:
  unsigned int bufferSize;
  unsigned int size;

  EBO(const std::vector<unsigned int> &, GLenum = GL_STATIC_DRAW);
  /* 不允许拷贝构造 / 赋值构造 / 转移 */
  EBO(EBO &&) = delete;
  EBO(EBO &) = delete;
  EBO &operator=(EBO &) = delete;
  EBO &operator=(EBO &&) = delete;

  ~EBO();

  void use() const;
};

class VAO {
private:
  std::shared_ptr<Program> program;
  unsigned int instance;

public:
  VAO(std::shared_ptr<Program> program);

  /* 不允许拷贝构造 / 赋值构造 / 转移 */
  VAO(VAO &&);
  VAO(VAO &) = delete;
  VAO &operator=(VAO &) = delete;
  VAO &operator=(VAO &&) = delete;
  ~VAO();

  void use();

  void useVBO(const VBO &vbo, const std::vector<VBOUsage>);
};
} // namespace huigl