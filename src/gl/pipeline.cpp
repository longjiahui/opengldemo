#include "gl/pipeline.hpp"
#include "iostream"
using namespace huigl;
using namespace std;

// const char *vertexName = "vertexPosition";

void Pipeline::useGLMesh(GLMesh &mesh, vector<VBOUsage> const &vboUsages) {
  auto vbo = mesh.getVBO();
  this->ebo = mesh.getEBO();
  this->vao = make_shared<VAO>(this->program);
  this->vao->useVBO(*vbo, vboUsages);
}

void Pipeline::drawElements() {
  this->program->use();
  this->vao->use();
  this->ebo->use();
  glDrawElements(GL_TRIANGLES, this->ebo->size, GL_UNSIGNED_INT, 0);
}

void Pipeline::drawArrays(unsigned int size) {
  this->program->use();
  this->vao->use();
  glDrawArrays(GL_TRIANGLES, 0, size);
}

void Pipeline::setTexture(unsigned short index, const std::string name,
                          Texture &texture) {
  glActiveTexture(GL_TEXTURE0 + index);
  this->setUniform(name, index);
  texture.use();
}

void Pipeline::setUniform(const std::string name, float val) {
  this->program->use();
  glUniform1f(this->program->getUniformLocation(name), val);
}
void Pipeline::setUniform(const std::string name, glm::mat4 const &val) {
  this->program->use();
  glUniformMatrix4fv(this->program->getUniformLocation(name), 1, GL_FALSE,
                     &val[0][0]);
}
void Pipeline::setUniform(const std::string name, int val) {
  this->program->use();
  glUniform1i(this->program->getUniformLocation(name), val);
}
void Pipeline::setUniform(const std::string name, unsigned short val) {
  this->program->use();
  glUniform1i(this->program->getUniformLocation(name), val);
}
void Pipeline::setUniform(const std::string name, double val) {
  this->program->use();
  glUniform1d(this->program->getUniformLocation(name), val);
}