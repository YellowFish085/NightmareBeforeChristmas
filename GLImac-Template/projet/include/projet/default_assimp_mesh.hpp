#pragma once

#include <stdlib.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <string>

#include <cstddef>
#include <cmath>

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "default_assimp_texture.hpp"

#define INVALID_OGL_VALUE 0xffffffff

namespace Projet
{
  class Mesh
  {
  public:
    Mesh();
    ~Mesh();

    // Charge un fichier 3D
    bool LoadMesh(const char* filename);
    // Affiche le contenu de la scene
    void Render();

  private:
    // Initialise l'objet en fonction des données contenues dans la scene
    bool InitFromScene(const aiScene* pScene, const char* filename);
    // Initialise les structures du vecteur m_Entries
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const char* filename);
    void Clear();

    #define INVALID_MATERIAL 0xFFFFFFFF


    struct Vertex
    {
      glm::vec3 m_pos;
      glm::vec2 m_tex;
      glm::vec3 m_normal;

      Vertex() {}

      Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
      {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
      }
    };

    // Chaque structure correspond à un maillage de l'objet aiScene
    struct MeshEntry {
      MeshEntry();
      ~MeshEntry();

      void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

      GLuint VB;
      GLuint IB;
      unsigned int NumIndices;
      unsigned int MaterialIndex;
    };

    // Vecteur de structures MeshEntry
    std::vector<MeshEntry> m_Entries;
    // Vecteur pour les textures
    std::vector<Texture*> m_Textures;
  };

}
