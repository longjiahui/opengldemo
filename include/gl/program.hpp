#pragma once

#include "lib/glfw.hpp"
#include <functional>
#include <memory>
#include <string>

namespace huigl {

class Program {
private:
  unsigned int program;
  unsigned int vertexShader;
  unsigned int fragmentShader;
  std::string vertexSource;
  std::string fragmentSource;

  /* 根据内容设置program */
  void _setProgram(const char *, const char *);

public:
  static std::shared_ptr<Program> fromFile(const char *, const char *);
  static std::shared_ptr<Program> fromText(const char *, const char *);

  Program(const char *vss, const char *fss);
  /* 禁止 拷贝构造 / 赋值构造 / 转移 */
  Program(Program &&);
  Program &operator=(Program &&);
  Program(Program &) = delete;
  Program &operator=(Program &) = delete;
  ~Program();

  void use();
  void use(std::function<void()>);

  GLint getVariableLocation(const std::string);
  GLint getUniformLocation(const std::string);

  //   void setUniform(const std::string, float, float, float, float);
  //   void setUniform(const std::string, float, float, float);
  //   void setUniform(const std::string, float, float);
  //   void setUniform(const std::string, float);
};
} // namespace huigl