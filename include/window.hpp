#pragma once

// #include "cef.hpp"
#include <memory>
#include <functional>
#include "glfw.hpp"
#include "gl/context.hpp"

namespace huige
{
    typedef std::function<void(std::shared_ptr<GLFWwindow> &)> WindowDrawFunc;
    class Window
    {
    private:
        // std::shared_ptr<CEF> cef;

    public:
        Window(WindowDrawFunc);
        WindowDrawFunc draw;
        // void (*draw)(std::shared_ptr<GLFWwindow> &_);
        std::shared_ptr<GLFWwindow> window;
        void use();

        std::shared_ptr<VAO> createVAO();
    };
}