#pragma once

// #include "cef.hpp"
#include <memory>
#include <GLFW/glfw3.h>

namespace huige
{
    class Window
    {
    private:
        // std::shared_ptr<CEF> cef;

    public:
        Window(void (*draw)(std::shared_ptr<GLFWwindow> &_));
        void (*draw)(std::shared_ptr<GLFWwindow> &_);
        std::shared_ptr<GLFWwindow> window;
    };
}