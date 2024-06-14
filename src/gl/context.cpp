#include "gl/context.hpp"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace huige;
using namespace std;

VAO::VAO() { glGenVertexArrays(1, &(this->instance)); }
VAO::~VAO() { glDeleteVertexArrays(1, &this->instance); }

shared_ptr<VBO> VAO::createVBO(shared_ptr<vector<float>> vertices) {
  return make_shared<VBO>(vertices);
}
void VAO::use() { glBindVertexArray(this->instance); }
void VAO::use(VAOUseFunc func) const {
  glBindVertexArray(this->instance);
  func();
}

void VAO::useVBO(shared_ptr<VBO> vbo, GLint interval, GLint index) {
  this->use(([&]() {
    vbo->use();
    glVertexAttribPointer(index, interval, GL_FLOAT, GL_FALSE,
                          interval * sizeof(float), nullptr);
    glEnableVertexAttribArray(index);
  }));
}

void VAO::drawArray(shared_ptr<Program> program, GLsizei size, GLint offset,
                    GLenum mode) {
  this->use([&]() {
    program->use();
    glDrawArrays(mode, offset, size);
  });
}

VBO::VBO(std::shared_ptr<std::vector<float>> vertices, GLenum usage) {
  glGenBuffers(1, &this->instance);
  this->use();
  glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float),
               vertices->data(), GL_STATIC_DRAW);
}

void VBO::use() { glBindBuffer(GL_ARRAY_BUFFER, this->instance); }

VBO::~VBO() { glDeleteBuffers(1, &this->instance); }

Program::Program(Program &&program) {
  this->program = program.program;
  this->vertexShader = program.vertexShader;
  this->fragmentShader = program.fragmentShader;
  this->vertexSource = program.vertexSource;
  this->fragmentSource = program.fragmentSource;
  program.program = 0;
  program.vertexShader = 0;
  program.fragmentShader = 0;
  program.vertexSource = nullptr;
  program.fragmentSource = nullptr;
}

Program::Program(const char *vertexPath, const char *fragmentPath) {
  ifstream vertexFile(vertexPath, ios_base::in);
  this->vertexSource = string(istreambuf_iterator<char>(vertexFile),
                              istreambuf_iterator<char>());
  vertexFile.close();
  ifstream fragmentfile(fragmentPath, ios_base::in);
  this->fragmentSource = string(istreambuf_iterator<char>(fragmentfile),
                                istreambuf_iterator<char>());
  fragmentfile.close();

  this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  auto pFragmentSource = &fragmentSource[0];
  auto pVertexSource = &vertexSource[0];
  glShaderSource(this->vertexShader, 1, &pVertexSource, nullptr);
  glShaderSource(this->fragmentShader, 1, &pFragmentSource, nullptr);
  glCompileShader(this->vertexShader);
  glCompileShader(this->fragmentShader);
  this->program = glCreateProgram();
  glAttachShader(this->program, this->vertexShader);
  glAttachShader(this->program, this->fragmentShader);
  glLinkProgram(this->program);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "vertex shader compile failed!\n"
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << infoLog
              << std::endl;
  }
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "fragment shader compile failed!\n" << infoLog << std::endl;
  }
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "shader program link failed!\n" << infoLog << std::endl;
  }
}

Program::~Program() {
  glDetachShader(this->program, this->vertexShader);
  glDetachShader(this->program, this->fragmentShader);
  glDeleteShader(this->vertexShader);
  glDeleteShader(this->fragmentShader);
  glDeleteProgram(this->program);
}

void Program::use() { glUseProgram(this->program); }
void Program::use(std::function<void()> callback) {
  this->use();
  callback();
}
GLint Program::getVariableLocation(const string name) {
  return glGetAttribLocation(this->program, &name[0]);
}
GLint Program::getUniformLocation(const string name) {
  return glGetUniformLocation(this->program, &name[0]);
}
void Program::setUniform(const std::string name, float x, float y, float z,
                         float w) {
  this->use();
  glUniform4f(this->getUniformLocation(&name[0]), x, y, z, w);
}
void Program::setUniform(const std::string name, float x, float y, float z) {
  this->use();
  glUniform3f(this->getUniformLocation(&name[0]), x, y, z);
}
void Program::setUniform(const std::string name, float x, float y) {
  this->use();
  glUniform2f(this->getUniformLocation(&name[0]), x, y);
}
void Program::setUniform(const std::string name, float x) {
  this->use();
  glUniform1f(this->getUniformLocation(&name[0]), x);
}