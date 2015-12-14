#include "projet/Mesh.hpp"

/* CONSTRUCTORS */
/* Default */
Mesh::Mesh() :
  _materialIndex(UNDEFINED) {}

/* Others */
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, unsigned int materialIndex) :
  _vertices(vertices), _indices(indices), _materialIndex(materialIndex) {}

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
unsigned int Mesh::getMaterialIndex() const {
  return _materialIndex;
}

Vertex* Mesh::getVertices() {
  if (_vertices.size() <= 0) {
    return NULL;
  }
  return _vertices.data();
}

uint32_t* Mesh::getIndices() {
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
