#pragma once

#include "glbase.hpp"
#include "mesh.hpp"
#include "program.hpp"

#include <memory>

namespace huigl {

class Pipeline {
private:
  std::shared_ptr<Program> program;
  std::shared_ptr<VAO> vao;
  std::shared_ptr<EBO> ebo;
  unsigned int triangleAmount;

public:
  Pipeline(const char *vp, const char *fp)
      : program(Program::fromFile(vp, fp)) {};

  void useMesh(Mesh &);
  void setUniform(const std::string, float);
  void setUniform(const std::string name, glm::mat4 const &val);

  void draw();
};

} // namespace huigl