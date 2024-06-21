#include "win/window.hpp"
#include <iostream>
#include <memory>

using namespace huigl;
using namespace std;

auto Window::_wins = unordered_map<GLFWwindow *, Window *>();

void Window::_init() {
  this->window = shared_ptr<GLFWwindow>(
      glfwCreateWindow(800, 600, "Window", nullptr, nullptr),
      [](auto p) { glfwDestroyWindow(p); });
  Window::_wins[this->window.get()] = this;
  glfwSetFramebufferSizeCallback(this->window.get(),
                                 [](auto window, auto width, auto height) {
                                   glViewport(0, 0, width, height);
                                   auto w = Window::_wins[window];
                                   w->aspect = width / height;
                                   w->_resize(w->window, width, height);
                                 });
}
Window::Window() { this->_init(); }
Window::~Window() { Window::_wins.erase(this->window.get()); }
Window::Window(WindowDrawFunc draw) {
  this->_init();
  this->setDraw(draw);
}

void Window::setDraw(WindowDrawFunc draw) { this->_draw = draw; }
void Window::setResize(WindowResizeFunc resize, bool immediate) {
  this->_resize = resize;
  if (immediate) {
    int w, h;
    glfwGetWindowSize(this->window.get(), &w, &h);
    this->_resize(this->window, w, h);
  }
}
void Window::draw() {
  this->use();
  this->_draw(this->window);
  glfwSwapBuffers(this->window.get());
  glfwPollEvents();
}

void Window::use() {
  auto ctx = glfwGetCurrentContext();
  if (ctx != this->window.get()) {
    glfwMakeContextCurrent(this->window.get());
  }
}