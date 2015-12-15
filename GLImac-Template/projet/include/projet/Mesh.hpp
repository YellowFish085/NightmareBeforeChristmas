#include <vector>

#include "projet/Vertex.hpp"

#define UNDEFINED -1 // Used if materialIndex is not defined

class Mesh {

  /* ATTRIBUTES */
  private :
    std::vector<Vertex> _vertices; // VBO
    std::vector<uint32_t> _indices; // IBO
    unsigned int _materialIndex; // Index of the material used on the mesh

  /* CONSTRUCTORS */
  public :
    /* Default */
    Mesh();

    /* Others */
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, unsigned int materialIndex);

  /* SETTERS */
    void setMaterialIndex (const unsigned int material);

    void addVertex(const Vertex& v);

    void addIndex(const uint32_t i);

  /* GETTERS */
    unsigned int getMaterialIndex() const;

    Vertex* getVertices();

    uint32_t* getIndices();

  /* OVERLOADING */
    /* Comparison operators */
    bool operator==(const Mesh& rh) const;

};
