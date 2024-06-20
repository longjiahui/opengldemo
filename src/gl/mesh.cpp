#include "gl/mesh.hpp"
#include "lib/assimp.hpp"

using namespace huigl;
using namespace std;

vector<float> Mesh::toBuffer() const {
  // auto buffer = new unsigned char[vertices.size() * 3 * sizeof(float)];
  auto buffer = vector<float>();
  for (auto v : this->vertices) {
    buffer.push_back(v.x);
    buffer.push_back(v.y);
    buffer.push_back(v.z);
  }
  return buffer;
}

shared_ptr<VBO> Mesh::getVBO() {
  if (!this->vbo) {
    this->vbo = make_shared<VBO>(this->toBuffer());
  }
  return this->vbo;
}
shared_ptr<EBO> Mesh::getEBO() {
  if (!this->ebo) {
    this->ebo = make_shared<EBO>(this->indices);
  }
  return this->ebo;
}

std::shared_ptr<Mesh> Mesh::fromFile(const char *p) {
  Assimp::Importer importer;
  auto scene = importer.ReadFile(p, 0);
  if (scene == nullptr) {
    throw runtime_error("Failed to load mesh from file: " + string(p));
  }
}
