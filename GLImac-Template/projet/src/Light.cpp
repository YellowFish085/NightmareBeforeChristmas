#include "projet/Light.hpp"

namespace Projet {
  Light::Light(glm::vec3 intensity) :
    _intensity(intensity)
  {};

  glm::vec3 Light::getIntensity()
  {}

  lightType Light::getType()
  {}
}
