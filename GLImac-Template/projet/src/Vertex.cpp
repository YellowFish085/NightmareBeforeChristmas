#include "projet/Vertex.hpp"

/* CONSTRUCTORS */
/* |_Default */
Vertex::Vertex() :
  _position(glm::vec3(0)), _textcoord(glm::vec2(0)), _normal(glm::vec3(0)){

};

/* |_Others */
Vertex::Vertex(glm::vec3 position, glm::vec2 textcoord, glm::vec3 normal) :
  _position(position), _textcoord(textcoord), _normal(normal){

};

Vertex::Vertex(float posX, float posY, float posZ, float tcX, float tcY, float normX, float normY, float normZ) :
  _position(glm::vec3(posX, posY, posZ)), _textcoord(glm::vec2(tcX, tcY)), _normal(glm::vec3(normX, normY, normZ)){

};

/* |_Operators */

bool Vertex::operator==(const Vertex& rhs) const {
  return(_position == rhs._position && _textcoord == rhs._textcoord && _normal == rhs._normal);
}
