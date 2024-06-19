#pragma once

#include "lib/glfw.hpp"
#include "window.hpp"
#include <memory>
#include <vector>

namespace huigl {
class Application {
private:
  static bool isGLFWInit;
  static bool isGLEWInit;
  std::shared_ptr<std::vector<std::shared_ptr<Window>>> wins;
  std::shared_ptr<std::vector<std::shared_ptr<Window>>> pendingWindow();

public:
  Application();
  std::shared_ptr<Window> createWindow();
  std::shared_ptr<Window> createWindow(WindowDrawFunc);
  void loop();
};
} // namespace huigl