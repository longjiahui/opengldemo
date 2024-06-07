#include "window.hpp"
#include <memory>
#include <iostream>

using namespace huige;

Window::Window(void (*draw)(std::shared_ptr<GLFWwindow> &_))
{
    this->window = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(
            800,
            600,
            "Window",
            nullptr,
            nullptr),
        [](auto p)
        {
            std::cout << "destruct glfwWindow" << std::endl;
            glfwDestroyWindow(p);
        });
    this->draw = draw;
}