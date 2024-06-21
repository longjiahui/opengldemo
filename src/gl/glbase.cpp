#include "gl/glbase.hpp"

#include <iostream>

using namespace huigl;
using namespace std;

VBO::VBO(const vector<float> &data, GLenum usage) {
  glGenBuffers(1, &this->instance);
  glBindBuffer(GL_ARRAY_BUFFER, this->instance);
  glBufferData(GL_ARRAY_BUFFER, data.size() * 3 * sizeof(float), data.data(),
               usage);
}
VBO::~VBO() { glDeleteBuffers(1, &this->instance); }

void VBO::use() const { glBindBuffer(GL_ARRAY_BUFFER, this->instance); }

EBO::EBO(const vector<unsigned int> &indices, GLenum usage) {
  glGenBuffers(1, &this->instance);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->instance);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               indices.data(), usage);
  this->bufferSize = indices.size() * sizeof(unsigned int);
  this->size = indices.size();
}
EBO::~EBO() { glDeleteBuffers(1, &this->instance); }

void EBO::use() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->instance); }

VAO::VAO(std::shared_ptr<Program> program) {
  this->program = program;
  glGenVertexArrays(1, &this->instance);
}
VAO::~VAO() { glDeleteVertexArrays(1, &this->instance); }

void VAO::use() { glBindVertexArray(this->instance); }

void VAO::useVBO(const VBO &vbo, const vector<VBOUsage> usages) {
  GLint totalLength = 0;
  for (auto usage : usages) {
    totalLength += usage.length;
  }
  this->use();
  vbo.use();
  for (auto usage : usages) {
    auto index = this->program->getVariableLocation(usage.name);
    // cout << "usage: " << index << " " << usage.length << " " << usage.offset
    //  << endl;
    glVertexAttribPointer(index, usage.length, GL_FLOAT, GL_FALSE,
                          totalLength * sizeof(float),
                          (void *)(usage.offset * sizeof(float)));
    glEnableVertexAttribArray(index);
  }
}
