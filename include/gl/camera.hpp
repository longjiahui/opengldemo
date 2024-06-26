#pragma once
#include "game/object.hpp"
#include "lib/glm.hpp"

namespace huigl {
class Camera : public Object {
public:
  Camera(glm::vec3 p = glm::vec3(0), glm::vec3 r = glm::vec3(0))
      : Object(p, r) {};
};
} // namespace huigl