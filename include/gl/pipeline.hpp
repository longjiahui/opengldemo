#pragma once

#include "glbase.hpp"
#include "mesh.hpp"
#include "program.hpp"
#include "texture.hpp"

#include <memory>

namespace huigl {

#define TEXTURE_INDEX(x) GL_TEXTURE##x

class Pipeline {
private:
  std::shared_ptr<Program> program;
  std::shared_ptr<VAO> vao;
  std::shared_ptr<EBO> ebo;
  unsigned int triangleAmount;

public:
  Pipeline(const char *vp, const char *fp)
      : program(Program::fromFile(vp, fp)) {};

  void useGLMesh(GLMesh &, std::vector<VBOUsage> const &);

  void setTexture(unsigned short, const std::string, Texture &);
  void setUniform(const std::string, float);
  void setUniform(const std::string, double);
  void setUniform(const std::string, int);
  void setUniform(const std::string, unsigned short);
  void setUniform(const std::string name, glm::mat4 const &val);

  void drawElements();
  void drawArrays(unsigned int);
};

} // namespace huigl