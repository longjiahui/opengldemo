#pragma once

#include "window.hpp"
#include <memory>
#include <vector>
#include <GLFW/glfw3.h>

namespace huige
{
    class Application
    {
        static bool isGLFWInit;

    private:
        std::shared_ptr<std::vector<std::shared_ptr<Window>>> wins;
        std::shared_ptr<std::vector<std::shared_ptr<Window>>> pendingWindow();

    public:
        Application();
        std::shared_ptr<Window> createWindow(void (*draw)(std::shared_ptr<GLFWwindow> &_));
        void loop();
    };
}