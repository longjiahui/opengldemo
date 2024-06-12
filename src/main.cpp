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
  auto win = application.createWindow([](auto _) {});
  shared_ptr<huige::Program> program =
      make_shared<huige::Program>("frag.glsl", "color.glsl");
  huige::VAO vao;
  vao.init();
  shared_ptr<huige::VBO> vbo = vao.createVBO(make_shared<vector<float>>(
      vector<float>({-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f})));
  vao.useVBO(vbo, 3);
  win->draw = [&](auto win)
  { 
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    vao.drawArray(program, 3); };
  application.loop();
  return 0;
}
