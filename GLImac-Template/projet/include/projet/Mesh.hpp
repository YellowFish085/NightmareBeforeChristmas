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

    /* Copy */
    Mesh(const Mesh& meshToCopy);

  /* SETTERS */
    void setMaterialIndex (const unsigned int material);

    void addVertex(const Vertex& v);

    void addIndex(const uint32_t i);

  /* GETTERS */
    const unsigned int getMaterialIndex() const;

    const Vertex* getVertices() const;

    const uint32_t* getIndices() const;

  /* OVERLOADING */
    /* Comparison operators */
    bool operator==(const Mesh& rh) const;

  /* OTHER METHODS */
    const unsigned int nbVertices() const;

    const unsigned int nbIndices() const;

    const unsigned int nbFaces() const; // A face is a triangle

};
