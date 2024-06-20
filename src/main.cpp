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
  auto texture = huigl::Texture::fromFile("image/image.jpg");
  p->setTexture(0, "texture1", *texture);
  auto mesh = huigl::Mesh(vector<vector<float>>(
      {{-0.5f, -0.5f, -0.5f, 0.0f, 0.0f}, {0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
       {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},   {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
       {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f},  {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},

       {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},  {0.5f, -0.5f, 0.5f, 1.0f, 0.0f},
       {0.5f, 0.5f, 0.5f, 1.0f, 1.0f},    {0.5f, 0.5f, 0.5f, 1.0f, 1.0f},
       {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f},   {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},

       {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f},   {-0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
       {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
       {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},  {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f},

       {0.5f, 0.5f, 0.5f, 1.0f, 0.0f},    {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
       {0.5f, -0.5f, -0.5f, 0.0f, 1.0f},  {0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
       {0.5f, -0.5f, 0.5f, 0.0f, 0.0f},   {0.5f, 0.5f, 0.5f, 1.0f, 0.0f},

       {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
       {0.5f, -0.5f, 0.5f, 1.0f, 0.0f},   {0.5f, -0.5f, 0.5f, 1.0f, 0.0f},
       {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},  {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},

       {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f},  {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
       {0.5f, 0.5f, 0.5f, 1.0f, 0.0f},    {0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
       {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f},   {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f}}));
  // vector<unsigned int>({0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,
  //                       8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12,
  //                       16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20}));
  p->useMesh(mesh, vector<huigl::VBOUsage>(
                       {{"vertexPosition", 0, 3}, {"textureCoord", 3, 2}}));
  win->setResize(
      [&](auto, auto w, auto h) {
        p->setUniform("projection",
                      glm::translate(glm::perspective(glm::radians(45.0f),
                                                      (float)(w) / float(h),
                                                      0.1f, 100.0f),
                                     glm::vec3(0.3f, 0.3f, -4.0f)));
      },
      true);
  win->setDraw([&](auto win) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    p->setUniform("time", glfwGetTime());
    p->setUniform(
        "transform",
        glm::translate(transformMatrix,
                       glm::vec3(glm::sin(glfwGetTime()) * 1.0f, 0.0f, 0.0f)));
    p->drawArrays(36);
  });
  application.loop();
  return 0;
}
