#pragma once
#include "lib/glm.hpp"

namespace huigl {
class Object {
public:
  glm::vec3 position;
  glm::vec3 rotation;
  Object(glm::vec3 p = glm::vec3(0), glm::vec3 r = glm::vec3(0))
      : position(p), rotation(r) {};
};
} // namespace huigl