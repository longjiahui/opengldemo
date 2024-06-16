#include "lib/glfw.hpp"

#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl/huige.hpp"
#include "win/application.hpp"
#include "win/window.hpp"

using namespace std;

int main(void) {
  huige::Application application;
  auto win = application.createWindow();
  shared_ptr<huige::Program> program =
      make_shared<huige::Program>("glsl/vertex.glsl", "glsl/frag.glsl");
  auto vao = win->createVAO();
  shared_ptr<huige::VBO> vbo =
      vao->createVBO(make_shared<vector<float>>(vector<float>(
          {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f})));
  vao->useVBO(*vbo, {{
                        program->getVariableLocation("aPos"),
                        0,
                        3,
                    }});
  win->setDraw([&](auto win) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    program->setUniform("time", glfwGetTime());
    vao->drawArray(program, 3);
  });
  application.loop();
  return 0;
}
