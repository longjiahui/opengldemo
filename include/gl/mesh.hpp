#pragma once

#include <vector>

#include "lib/glm.hpp"

#include "gl/glbase.hpp"

namespace huigl {
class GLMesh {

private:
  std::shared_ptr<VBO> vbo;
  std::shared_ptr<EBO> ebo;
  std::vector<std::vector<float>> vertices;
  std::vector<unsigned int> indices;

public:
  static std::shared_ptr<GLMesh> fromFile(const char *p);

  GLMesh(std::vector<std::vector<float>> vertices,
         std::vector<unsigned int> indices = std::vector<unsigned int>())
      : vertices(vertices), indices(indices) {}
  //   std::vector<glm::vec3> normals;
  std::vector<float> toBuffer() const;
  std::shared_ptr<VBO> getVBO();
  std::shared_ptr<EBO> getEBO();
};
} // namespace huigl