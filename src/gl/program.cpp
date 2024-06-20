#include "gl/program.hpp"
#include "util.hpp"
#include <iostream>

using namespace huigl;
using namespace std;

// Program::Program(Program &&program) {
//   this->program = program.program;
//   this->vertexShader = program.vertexShader;
//   this->fragmentShader = program.fragmentShader;
//   this->vertexSource = program.vertexSource;
//   this->fragmentSource = program.fragmentSource;
//   program.program = 0;
//   program.vertexShader = 0;
//   program.fragmentShader = 0;
//   program.vertexSource = nullptr;
//   program.fragmentSource = nullptr;
// }

void Program::_setProgram(const char *vss, const char *fss) {
  this->vertexSource = vss;
  this->fragmentSource = fss;
  this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->vertexShader, 1, &vss, nullptr);
  glShaderSource(this->fragmentShader, 1, &fss, nullptr);
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
    throw runtime_error("vertex shader compile failed!"s + infoLog);
  }
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    throw runtime_error("fragment shader compile failed!"s + infoLog);
  }
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    throw runtime_error("program link failed!"s + infoLog);
  }
}
Program::Program(Program &&p) {
  this->program = p.program;
  this->vertexShader = p.vertexShader;
  this->fragmentShader = p.fragmentShader;
  this->vertexSource = p.vertexShader;
  this->fragmentSource = p.fragmentSource;
}
Program &Program::operator=(Program &&p) {
  this->program = p.program;
  this->vertexShader = p.vertexShader;
  this->fragmentShader = p.fragmentShader;
  this->vertexSource = p.vertexShader;
  this->fragmentSource = p.fragmentSource;
  return *this;
}

Program::Program(const char *vss, const char *fss) {
  this->_setProgram(vss, fss);
}
shared_ptr<Program> Program::fromText(const char *vss, const char *fss) {
  return make_shared<Program>(vss, fss);
}
shared_ptr<Program> Program::fromFile(const char *vp, const char *fp) {
  string vertexSource = huigl::readFile(vp);
  string fragmentSource = huigl::readFile(fp);
  return make_shared<Program>(vertexSource.c_str(), fragmentSource.c_str());
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