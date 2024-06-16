#pragma once

#include "lib/glfw.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace huige {
class VAO;
class VBO;

typedef struct {
  GLint index;
  GLint offset;
  GLint length;
  GLint step;
} VBOUsage;

class Program {
private:
  unsigned int program;
  unsigned int vertexShader;
  unsigned int fragmentShader;
  std::string vertexSource;
  std::string fragmentSource;

public:
  Program(const char *, const char *);

  /* 不允许拷贝构造和赋值构造，只允许转移 */
  Program(Program &&);
  Program(Program &) = delete;
  Program &operator=(Program &) = delete;
  ~Program();

  void use();
  void use(std::function<void()>);
  GLint getVariableLocation(const std::string);
  GLint getUniformLocation(const std::string);

  void setUniform(const std::string, float, float, float, float);
  void setUniform(const std::string, float, float, float);
  void setUniform(const std::string, float, float);
  void setUniform(const std::string, float);
};
class VBO {
private:
  unsigned int instance;
  std::shared_ptr<std::vector<float>> vertices;

public:
  VBO(std::shared_ptr<std::vector<float>>, GLenum usage = GL_STATIC_DRAW);
  /* 不允许拷贝构造和赋值构造，只允许转移 */
  VBO(VBO &&);
  VBO(VBO &) = delete;
  VBO &operator=(VBO &) = delete;
  ~VBO();

  void use() const;
  // void init(std::shared_ptr<std::vector<float>> vertices);
};

/* Draw Context */
// class GLDrawContext
// {
// private:
//     std::shared_ptr<GLContext> glContext;
//     std::shared_ptr<Program> program;
//     std::shared_ptr<GLVBO> VBO;

// public:
//     GLDrawContext(GLContext, std::shared_ptr<Program>,
//     std::shared_ptr<GLVBO>); void draw();
// };

/* A VAO */
typedef std::function<void()> VAOUseFunc;

class VAO {
private:
  unsigned int instance;

public:
  VAO();

  /* 不允许拷贝构造和赋值构造，只允许转移 */
  VAO(VAO &&);
  VAO(VAO &) = delete;
  VAO &operator=(VAO &) = delete;
  ~VAO();

  void use();
  void use(VAOUseFunc) const;

  std::shared_ptr<VBO> createVBO(std::shared_ptr<std::vector<float>> vertices);

  void useVBO(const VBO &vbo, const std::vector<VBOUsage> &);
  void drawArray(std::shared_ptr<Program>, GLsizei, GLint = 0,
                 GLenum = GL_TRIANGLES);
};

class Image {
private:
  void setImage(unsigned char *, const unsigned int &, const unsigned int &);

public:
  unsigned char *data;
  unsigned int width;
  unsigned int height;
  static std::shared_ptr<Image> load(const char *);
  Image();
  Image(unsigned char *data, unsigned int width, unsigned int height);

  /* 不允许拷贝构造和赋值构造，只允许转移 */
  Image(Image &&);
  Image(Image &) = delete;
  Image &operator=(Image &) = delete;

  ~Image();
};

class Texture {
public:
  Texture(const Image &);
  ~Texture();
  void use();

  /* 不允许拷贝构造、赋值、转移 */
  Texture(Texture &&) = delete;
  Texture(Texture &) = delete;
  Texture &operator=(Texture &) = delete;
private:
  unsigned int instance;
};

} // namespace huige