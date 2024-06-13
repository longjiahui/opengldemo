#pragma once

#include "window.hpp"
#include <memory>
#include <vector>
#include "glfw.hpp"

namespace huige
{
    class Application
    {
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
}