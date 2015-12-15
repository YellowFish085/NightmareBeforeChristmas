#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Vertex.hpp"

namespace Projet
{
  /**
   * Class Mesh
   **/
  class Mesh
  {
  public:
    Mesh(const glimac::FilePath* applicationPath);
    ~Mesh();
    // Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, unsigned int materialIndex);
    // Mesh(const Mesh& meshToCopy);

    bool loadMesh(const char* filename);  // Load 3D objet
    void render();                        // Render all the meshs
    
    /*
    void setMaterialIndex (const unsigned int material);
    void addVertex(const Vertex& v);
    void addIndex(const uint32_t i);

    const unsigned int getMaterialIndex() const;
    const Vertex* getVertices() const;
    const uint32_t* getIndices() const;

    bool operator==(const Mesh& rh) const;

    const unsigned int nbEntries() const;
    const unsigned int nbIndices() const;
    const unsigned int nbFaces() const; // A face is a triangle
    */

  private:
    bool init(const aiScene* scene, const char* filename);          // Initialize Mesh object
    void initMeshEntry(unsigned int id, const aiMesh* meshEntry);   // Initialize all meshes
    bool initMaterials(const aiScene* scene);                       // Initialize all textures

    #define INVALID_MATERIAL 0xFFFFFFFF

    // Each mesh in the loaded file is a struct
    struct MeshEntry {
      MeshEntry();
      ~MeshEntry();

      // Initialize the mesh struct
      void init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

      GLuint vb;                    // vbo
      GLuint ib;                    // ibo
      unsigned int numIndices;      // Number of indices in the mesh
      unsigned int materialIndex;   // Id of the texture linked to the mesh
    };

    const glimac::FilePath** _ApplicationPath;
    std::vector<MeshEntry> _entries;  // All the meshes
    std::vector<GLuint> _textures;    // All the textures
  };
}