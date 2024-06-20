#pragma once

// #include "cef.hpp"
// #include "gl/huigl.hpp"
#include "lib/glfw.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

namespace huigl {
typedef std::function<void(std::shared_ptr<GLFWwindow>)> WindowDrawFunc;
typedef std::function<void(std::shared_ptr<GLFWwindow>, unsigned int,
                           unsigned int)>
    WindowResizeFunc;
class Window {
private:
  void _init();
  WindowDrawFunc _draw;
  // std::shared_ptr<CEF> cef;
  static std::unordered_map<GLFWwindow *, Window *> _wins;

public:
  float aspect;
  WindowResizeFunc _resize;

  Window();
  ~Window();
  Window(WindowDrawFunc);
  void setDraw(WindowDrawFunc);
  void setResize(WindowResizeFunc, bool immediate = false);
  void draw();
  // void (*draw)(std::shared_ptr<GLFWwindow> &_);
  std::shared_ptr<GLFWwindow> window;
  void use();
};
} // namespace huigl