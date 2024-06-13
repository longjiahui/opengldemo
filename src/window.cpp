#include "window.hpp"
#include <memory>
#include <iostream>

using namespace huige;
using namespace std;

Window::Window(WindowDrawFunc draw)
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
    glfwSetFramebufferSizeCallback(this->window.get(), [](auto window, auto width, auto height)
                                   { glViewport(0, 0, width, height); });
    this->draw = draw;
}

void Window::use()
{
    auto ctx = glfwGetCurrentContext();
    if (ctx != this->window.get())
    {
        glfwMakeContextCurrent(this->window.get());
    }
}

shared_ptr<VAO> Window::createVAO()
{
    this->use();
    return make_shared<VAO>();
}