#include "win/window.hpp"
#include <iostream>
#include <memory>

using namespace huige;
using namespace std;

void Window::_init() {
  this->window = shared_ptr<GLFWwindow>(
      glfwCreateWindow(800, 600, "Window", nullptr, nullptr), [](auto p) {
        cout << "destruct glfwWindow" << endl;
        glfwDestroyWindow(p);
      });
  glfwSetFramebufferSizeCallback(this->window.get(),
                                 [](auto window, auto width, auto height) {
                                   glViewport(0, 0, width, height);
                                 });
}
Window::Window() { this->_init(); }
Window::Window(WindowDrawFunc draw) {
  this->_init();
  this->setDraw(draw);
}

void Window::setDraw(WindowDrawFunc draw) { this->_draw = draw; }
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

shared_ptr<VAO> Window::createVAO() {
  this->use();
  return make_shared<VAO>();
}