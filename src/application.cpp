#include "application.hpp"
#include "stdlib.h"
#include <iostream>
using namespace huige;
using namespace std;

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
    this->wins = make_shared<vector<shared_ptr<Window>>>();
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

shared_ptr<Window> Application::createWindow(void (*draw)(shared_ptr<GLFWwindow> &_))
{
    shared_ptr<Window> w = make_shared<Window>(draw);
    this->wins->push_back(w);
    return w;
}

shared_ptr<vector<shared_ptr<Window>>> Application::pendingWindow()
{
    auto pwins = make_shared<vector<shared_ptr<Window>>>();
    for (short i = 0; i < this->wins->size(); i++)
    {
        if (!glfwWindowShouldClose(this->wins->at(i)->window.get()))
        {
            pwins->push_back(this->wins->at(i));
        }
    }
    return pwins;
}