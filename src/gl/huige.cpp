#include "gl/huige.hpp"
#include "lib/glfw.hpp"
#include "lib/stb_image.hpp"
#include "util.hpp"

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
void VAO::useVBO(const VBO &vbo, const std::vector<VBOUsage> &usages) {
  GLint totalLength = 0;
  for (auto usage : usages) {
    totalLength += usage.length;
  }
  this->use([&vbo, &usages, &totalLength]() {
    vbo.use();
    for (auto usage : usages) {
      glVertexAttribPointer(usage.index, usage.length, GL_FLOAT, GL_FALSE,
                            totalLength * sizeof(float),
                            (void *)(usage.offset * sizeof(float)));
      glEnableVertexAttribArray(usage.index);
    }
  });
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

void VBO::use() const { glBindBuffer(GL_ARRAY_BUFFER, this->instance); }

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
  this->vertexSource = huige::readFile(vertexPath);
  this->fragmentSource = huige::readFile(fragmentPath);

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

void Image::setImage(unsigned char *data, const unsigned int &width,
                     const unsigned int &height) {
  this->data = data;
  this->width = width;
  this->height = height;
}

shared_ptr<Image> Image::load(const char *path) {
  int width, height, channels;
  return make_shared<Image>(stbi_load(path, &width, &height, &channels, 0), width, height);
}

Image::Image(unsigned char *data, unsigned int width, unsigned int height) {
  this->setImage(data, width, height);
}

Image::Image(Image && image)
{
  this->data = image.data;
  this->width = image.width;
  this->height = image.height;
  image.data = nullptr;
  image.width = NULL;
  image.height = NULL;
}

Image::~Image(){
  stbi_image_free(this->data);
}

void Texture::use(){
  glBindTexture(GL_TEXTURE_2D, this->instance);
}

Texture::Texture(const Image &image){
  glGenTextures(1, &this->instance);
  this->use();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture(){
  glDeleteTextures(1, &this->instance);
}