#include "window.hpp"
#include <memory>
#include <iostream>

using namespace huige;
using namespace std;

Window::Window(void (*draw)(shared_ptr<GLFWwindow> &_))
{
    this->window = shared_ptr<GLFWwindow>(
        glfwCreateWindow(
            800,
            600,
            "Window",
            nullptr,
            nullptr),
        [](auto p)
        {
            cout << "destruct glfwWindow" << endl;
            glfwDestroyWindow(p);
        });
    this->draw = draw;
}