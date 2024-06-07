#include "application.hpp"
#include "stdlib.h"
#include <iostream>
using namespace huige;

bool Application::isGLFWInit = false;

Application::Application()
{
    if (!Application::isGLFWInit)
    {
        Application::isGLFWInit = true;
        glfwInit();
        atexit([]()
               { glfwTerminate(); });
    }
    this->wins = std::shared_ptr<std::vector<std::shared_ptr<Window>>>(new std::vector<std::shared_ptr<Window>>());
}

void Application::loop()
{
    auto pWins = this->pendingWindow();
    while (pWins->size() > 0)
    {
        for (auto w : *pWins)
        {
            GLFWwindow *glfwWindow = w->window.get();
            glfwMakeContextCurrent(glfwWindow);
            w->draw(w->window);
            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
        pWins = this->pendingWindow();
    }
}

std::shared_ptr<Window> Application::createWindow(void (*draw)(std::shared_ptr<GLFWwindow> &_))
{
    std::shared_ptr<Window> w(new Window(draw), [](auto p)
                              {
        std::cout << "destruct window" << std::endl;
        delete p; });
    this->wins->push_back(w);
    return w;
}

std::shared_ptr<std::vector<std::shared_ptr<Window>>> Application::pendingWindow()
{
    auto pwins = std::shared_ptr<std::vector<std::shared_ptr<Window>>>(new std::vector<std::shared_ptr<Window>>());
    for (short i = 0; i < this->wins->size(); i++)
    {
        if (!glfwWindowShouldClose(this->wins->at(i)->window.get()))
        {
            pwins->push_back(this->wins->at(i));
        }
    }
    return pwins;
}