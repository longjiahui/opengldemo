#include "gl/pipeline.hpp"
#include "iostream"
using namespace huigl;
using namespace std;

const char *vertexName = "vertexPosition";

void Pipeline::useMesh(Mesh &mesh) {
  auto vbo = mesh.getVBO();
  this->ebo = mesh.getEBO();
  this->vao = make_shared<VAO>(this->program);
  this->vao->useVBO(*vbo, vector<VBOUsage>({{vertexName, 0, 3, 0}}));
}

void Pipeline::draw() {
  this->program->use();
  this->vao->use();
  this->ebo->use();
  glDrawElements(GL_TRIANGLES, this->ebo->size, GL_UNSIGNED_INT, 0);
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