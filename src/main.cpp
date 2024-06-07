#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "application.hpp"
#include "window.hpp"

using namespace std;

int main(void)
{
    huige::Application application;
    application.createWindow([](auto win)
                             {
        glClearColor(184.0f / 255.0f, 213.0f / 255.0f, 238.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); });
    application.createWindow([](auto win)
                             {
        glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT); });
    application.loop();
    return 0;
}
