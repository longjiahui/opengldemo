#include "gl/mesh.hpp"
#include "lib/assimp.hpp"

#include <stdexcept>

using namespace huigl;
using namespace std;

vector<float> GLMesh::toBuffer() const {
  // auto buffer = new unsigned char[vertices.size() * 3 * sizeof(float)];
  auto buffer = vector<float>();
  for (auto v : this->vertices) {
    for (auto d : v) {
      buffer.push_back(d);
    }
  }
  return buffer;
}

shared_ptr<VBO> GLMesh::getVBO() {
  if (!this->vbo) {
    this->vbo = make_shared<VBO>(this->toBuffer());
  }
  return this->vbo;
}
shared_ptr<EBO> GLMesh::getEBO() {
  if (!this->ebo) {
    this->ebo = make_shared<EBO>(this->indices);
  }
  return this->ebo;
}

std::shared_ptr<GLMesh> GLMesh::fromFile(const char *p) {
  Assimp::Importer importer;
  auto scene = importer.ReadFile(p, 0);
  if (scene == nullptr) {
    throw runtime_error("Failed to load GLMesh from file: " + string(p));
  }
}
