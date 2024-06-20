#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "lib/glfw.hpp"
#include "lib/glm.hpp"

#include "gl/mesh.hpp"
#include "gl/pipeline.hpp"

#include "win/application.hpp"
#include "win/window.hpp"

using namespace std;
using namespace glm;

int main(void) {
  huigl::Application application;
  auto win = application.createWindow();
  auto transformMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0));
  auto p = new huigl::Pipeline("glsl/vertex.glsl", "glsl/frag.glsl");
  auto mesh =
      huigl::Mesh(vector<glm::vec3>({
                      {-0.5f, 0.5f, -4.0f},
                      {0.5f, 0.5f, -4.0f},
                      {0.5f, -0.5f, -4.0f},
                      {-0.5f, -0.5f, -4.0f},

                      {-0.5f, 0.5f, -10.0f},
                      {0.5f, 0.5f, -10.0f},
                      {0.5f, -0.5f, -10.0f},
                      {-0.5f, -0.5f, -10.0f},
                  }),
                  vector<unsigned int>({0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
                                        0, 1, 5, 0, 5, 4, 3, 2, 6, 3, 6, 7,
                                        1, 2, 6, 1, 6, 5, 0, 3, 7, 0, 7, 4}));
  p->useMesh(mesh);
  win->setResize(
      [&](auto, auto w, auto h) {
        p->setUniform("projection",
                      glm::perspective(glm::radians(45.0f),
                                       (float)(w) / float(h), 0.1f, 100.0f));
      },
      true);
  p->setUniform("transform", transformMatrix);
  win->setDraw([&](auto win) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    p->setUniform("time", glfwGetTime());
    p->draw();
  });
  application.loop();
  return 0;
}
