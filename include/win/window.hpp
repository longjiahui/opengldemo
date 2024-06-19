#pragma once

// #include "cef.hpp"
#include "gl/huigl.hpp"
#include "lib/glfw.hpp"

#include <functional>
#include <memory>

namespace huigl {
typedef std::function<void(std::shared_ptr<GLFWwindow>)> WindowDrawFunc;
class Window {
private:
  void _init();
  WindowDrawFunc _draw;
  // std::shared_ptr<CEF> cef;

public:
  Window();
  Window(WindowDrawFunc);
  void setDraw(WindowDrawFunc);
  void draw();
  // void (*draw)(std::shared_ptr<GLFWwindow> &_);
  std::shared_ptr<GLFWwindow> window;
  void use();

  std::shared_ptr<VAO> createVAO();
};
} // namespace huigl