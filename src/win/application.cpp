#include "win/application.hpp"
#include "stdlib.h"
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
using namespace huigl;
using namespace std;

bool Application::isGLFWInit = false;
bool Application::isGLEWInit = false;

Application::Application() {
  if (!Application::isGLFWInit) {
    Application::isGLFWInit = true;
    glfwInit();
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    atexit([]() { glfwTerminate(); });
  }
  this->wins = make_shared<vector<shared_ptr<Window>>>();
}

void Application::loop() {
  auto pWins = this->pendingWindow();
  while (pWins->size() > 0) {
    for (auto w : *pWins) {
      w->draw();
    }
    pWins = this->pendingWindow();
    // 用来做一个 帧数限制
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}

void initGlew() {
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    throw runtime_error("Failed to initialize GLEW: " +
                        string((char *)glewGetErrorString(err)));
  }
  glEnable(GL_DEPTH_TEST);
  cout << "current openGL Version: " << glGetString(GL_VERSION) << endl;
  cout << "current GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
       << endl;
}

shared_ptr<Window> Application::createWindow() {
  shared_ptr<Window> w = make_shared<Window>();
  if (!Application::isGLEWInit) {
    Application::isGLEWInit = true;
    w->use();
    initGlew();
  }
  this->wins->push_back(w);
  return w;
}
shared_ptr<Window> Application::createWindow(WindowDrawFunc draw) {
  auto w = this->createWindow();
  w->setDraw(draw);
  return w;
}

shared_ptr<vector<shared_ptr<Window>>> Application::pendingWindow() {
  auto pwins = make_shared<vector<shared_ptr<Window>>>();
  for (short i = 0; i < this->wins->size(); i++) {
    if (!glfwWindowShouldClose(this->wins->at(i)->window.get())) {
      pwins->push_back(this->wins->at(i));
    }
  }
  return pwins;
}