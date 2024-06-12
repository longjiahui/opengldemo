#include "glfw.hpp"

#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "application.hpp"
#include "gl/context.hpp"
#include "window.hpp"

using namespace std;

int main(void)
{
  huige::Application application;
  application.createWindow([&](auto win)
                           {
    shared_ptr<huige::Program> program =
        make_shared<huige::Program>("frag.glsl", "color.glsl");
    huige::VAO vao;
    shared_ptr<huige::VBO> vbo = vao.createVBO(make_shared<vector<float>>(
        vector({-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f})));
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vao.useVBO(vbo, 3);
    vao.drawArray(program, 3); });
  application.loop();
  return 0;
}
