#include <glimac/glm.hpp>

namespace Projet
{
  class Vertex {
  /* CONSTRUCTORS */
  public:
    glm::vec3 _position;
    glm::vec2 _texCoords;
    glm::vec3 _normal;
    
  /* |_Default */
    Vertex();

  /* |_Others */
    Vertex(glm::vec3 position, glm::vec2 textcoord, glm::vec3 normal);

    Vertex(float posX, float posY, float posZ, float tcX, float tcY, float normX, float normY, float normZ);

  /* |_Copy */
    Vertex(const Vertex& vertexToCopy);

  /* OVERLOADING */
  /* Operators */
  /* |_Comparison operators */
    bool operator==(const Vertex& rhs) const;
  };
}