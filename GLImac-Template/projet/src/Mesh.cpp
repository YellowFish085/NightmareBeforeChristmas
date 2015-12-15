#include "projet/Mesh.hpp"

/* CONSTRUCTORS */
/* Default */
Mesh::Mesh() :
  _materialIndex(UNDEFINED) {

  }

/* Others */
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, unsigned int materialIndex) :
  _vertices(vertices),
  _indices(indices),
  _materialIndex(materialIndex) {

}

/* Copy */
Mesh::Mesh(const Mesh& meshToCopy) :
  _vertices(meshToCopy._vertices),
  _indices(meshToCopy._indices),
  _materialIndex(meshToCopy._materialIndex) {

}

/* SETTERS */
void Mesh::setMaterialIndex (const unsigned int material) {
  _materialIndex = material;
}

void Mesh::addVertex(const Vertex& v) {
  _vertices.push_back(v);
}

void Mesh::addIndex(const uint32_t i) {
  _indices.push_back(i);
}


/* GETTERS */
const unsigned int Mesh::getMaterialIndex() const {
  return _materialIndex;
}

const Vertex* Mesh::getVertices() const {
  if (_vertices.size() <= 0) {
    return NULL;
  }
  return _vertices.data();
}

const uint32_t* Mesh::getIndices() const {
  if (_indices.size() <= 0) {
    return NULL;
  }
  return _indices.data();
}

/* OVERLOADING */
/* Comparison operators */
bool Mesh::operator==(const Mesh& rhs) const {
  return (_vertices == rhs._vertices && _indices == rhs._indices && _materialIndex == rhs._materialIndex);
}

/* OTHER METHODS */
const unsigned int Mesh::nbVertices() const {
  return _vertices.size();
}

const unsigned int Mesh::nbIndices() const {
  return _indices.size();
}

const unsigned int Mesh::nbFaces() const {
  if (_indices.size() < 3) {
    return 0;
  }
  return _indices.size() / 3;
}
