# pragma once

#include <glimac/glm.hpp>

#include "Light.hpp"

namespace Projet {

  class PointLight : public Light
  {
    /* ATTRIBUTES */
  private:
    /* Same as Light */
    glm::vec3 _position;
    lightType _type;

  public:
    /* CONSTRUCTORS */
    PointLight(glm::vec3 intensity, glm::vec3 position);

    /* GETTERS */
    /* same as Light */
    glm::vec3 getIntensity();
    lightType getType();
    const glm::vec3 getPosition() const;
  };

}
