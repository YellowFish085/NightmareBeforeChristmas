#include "projet/Mesh.hpp"

namespace Projet
{
  Mesh::MeshEntry::MeshEntry()
  {
    numIndices    = 0;
    materialIndex = INVALID_MATERIAL;
  }

  Mesh::MeshEntry::~MeshEntry()
  {
    glDeleteBuffers(1, &vb);
    glDeleteBuffers(1, &ib);
  }

  void Mesh::MeshEntry::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
  {
    numIndices = indices.size();

    // Initialize vbo and ibo in the struct
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
  }

  Mesh::Mesh(const glimac::FilePath* applicationPath)
  {
    _ApplicationPath = &applicationPath;
  }

  Mesh::~Mesh()
  {

  }

  /*
  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, unsigned int materialIndex) :
    _vertices(vertices),
    _indices(indices),
    _materialIndex(materialIndex)
  {
  }

  Mesh::Mesh(const Mesh& meshToCopy) :
    _vertices(meshToCopy._vertices),
    _indices(meshToCopy._indices),
    _materialIndex(meshToCopy._materialIndex)
  {

  }
  */

  bool Mesh::loadMesh(const char* filename)
  {
    std::cout << "-- Mesh " << filename << " - initialisation..." << std::endl;

    bool ret = false;

    const glimac::FilePath* dir = *_ApplicationPath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    // If the file is loaded, the Mesh object can be initalized
    if (scene) {
      std::cout << "-- " << filename << " chargé..." << std::endl;
      ret = init(scene, filename);
    }
    else {
      std::cerr << "-- ERROR: Erreur lors du chargement du fichier 3D " << filename << std::endl;
    }

    return ret;
  }

  bool Mesh::init(const aiScene* scene, const char* filename)
  {
    // Meshes and textures vectors are resized
    _entries.resize(scene->mNumMeshes);
    _textures.resize(scene->mNumMaterials);

    // _entries is filled with all the meshes in the loaded file
    for (unsigned int i = 0; i < _entries.size(); i++) {
      const aiMesh* tmpMesh = scene->mMeshes[i];
      initMeshEntry(i, tmpMesh);
    }

    // Initialize the textures
    return initMaterials(scene);
  }

  void Mesh::initMeshEntry(unsigned int id, const aiMesh* meshEntry)
  {
    // The index of the material used by the mesh is stored
    _entries[id].materialIndex = meshEntry->mMaterialIndex;

    // Temp vectors filled with vertices and indices for the mesh faces
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Default value for the normal and tex corrds
    const aiVector3D defaultVector(0.0f, 0.0f, 0.0f);

    // vertices filled with all vertices
    for (unsigned int i = 0; i < meshEntry->mNumVertices; i++) {
      // Vertice position
      const aiVector3D* pos = &(meshEntry->mVertices[i]);
      // Normal
      const aiVector3D* norm = &(meshEntry->mNormals[i]) ? &(meshEntry->mNormals[i]) : &defaultVector;
      // Texture coords
      const aiVector3D* texCoords = meshEntry->HasTextureCoords(0) ? &(meshEntry->mTextureCoords[0][i]) : &defaultVector;

      // Create a point and store it
      Vertex v(glm::vec3(pos->x, pos->y, pos->z),
              glm::vec2(texCoords->x, texCoords->y),
              glm::vec3(norm->x, norm->y, norm->z));

      vertices.push_back(v);
    }

    // indices filled with the informations of the mesh faces
    for (unsigned int i = 0; i < meshEntry->mNumFaces; i++) {
      const aiFace& face = meshEntry->mFaces[i];

      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    // MeshEntry struct initialized in _entries
    _entries[id].init(vertices, indices);
  }

  bool Mesh::initMaterials(const aiScene* scene)
  {
    bool ret = true;

    const glimac::FilePath* dir = *_ApplicationPath;

    // Loading default texture
    std::unique_ptr<glimac::Image> defaultTex = loadImage(glimac::FilePath("Content/white.png"));

    if (defaultTex == NULL) {
      std::cerr << "-- Erreur lors du chargement de la texture par défaut " << glimac::FilePath("Content/white.png").dirPath() << std::endl;
      return false;
    }

    // All the textures are processed
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
      const aiMaterial* material = scene->mMaterials[i];

      _textures[i] = 0;

      // Only diffuse textures are processed
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString path;

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
          char filePath[256] = "";
          std::strcat(filePath, "Content/");
          std::strcat(filePath, path.data);

          std::unique_ptr<glimac::Image> tex = loadImage(glimac::FilePath(filePath));

          GLuint texId;
          glGenTextures(1, &texId);
          glBindTexture(GL_TEXTURE_2D, texId);

          // Using default texture if the correct texture was not loaded
          if (tex == NULL) {
            std::cerr << "-- Erreur lors du chargement de la texture " << filePath << std::endl;
            glTexImage2D(
              GL_TEXTURE_2D,
              0,
              GL_RGBA,
              defaultTex->getWidth(),
              defaultTex->getHeight(),
              0,
              GL_RGBA,
              GL_FLOAT,
              defaultTex->getPixels()
              );
            ret = false;
          }
          else {
            std::cout << "-- " << filePath << " chargée..." << std::endl;
            glTexImage2D(
              GL_TEXTURE_2D,
              0,
              GL_RGBA,
              tex->getWidth(),
              tex->getHeight(),
              0,
              GL_RGBA,
              GL_FLOAT,
              tex->getPixels()
              );
          }

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

          _textures[i] = texId;
        }
      }
    }

    return ret;
  }

  void Mesh::render()
  {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < _entries.size(); i++) {
      glBindBuffer(GL_ARRAY_BUFFER, _entries[i].vb);
      glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        0
        );
      glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (const GLvoid*) (offsetof(Vertex, _texCoords))
        );
      glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (const GLvoid*) (offsetof(Vertex, _normal))
        );

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _entries[i].ib);

      const unsigned int matIndex = _entries[i].materialIndex;

      if (matIndex < _textures.size() && _textures[matIndex]) {
        glBindTexture(GL_TEXTURE_2D, _textures[matIndex]);
      }

      glDrawElements(GL_TRIANGLES, _entries[i].numIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  void Mesh::setPosition(glm::vec3 position)
  {
    _position = position;
  }

  void Mesh::setAngle(float angle)
  {
    _angle = angle;
  }

  void Mesh::setRotAxe(glm::vec3 axis)
  {
    _rotAxe = axis;
  }

  void Mesh::setScale(glm::vec3 scale)
  {
    _scale = scale;
  }


  /*
  void Mesh::setMaterialIndex (const unsigned int material)
  {
    _materialIndex = material;
  }

  void Mesh::addVertex(const Vertex& v)
  {
    _vertices.push_back(v);
  }

  /*
  void Mesh::addIndex(const uint32_t i)
  {
    _indices.push_back(i);
  }

  const unsigned int Mesh::getMaterialIndex() const
  {
    return _materialIndex;
  }

  const Vertex* Mesh::getVertices() const
  {
    if (_vertices.size() <= 0) {
      return NULL;
    }
    return _vertices.data();
  }
  const uint32_t* Mesh::getIndices() const
  {
    if (_indices.size() <= 0) {
      return NULL;
    }
    return _indices.data();
  }

  bool Mesh::operator==(const Mesh& rhs) const
  {
    return (_vertices == rhs._vertices && _indices == rhs._indices && _materialIndex == rhs._materialIndex);
  }
  const unsigned int Mesh::nbEntries() const
  {
    return _entries.size();
  }

  const unsigned int Mesh::nbIndices() const
  {
    return _indices.size();
  }

  const unsigned int Mesh::nbFaces() const
  {
    if (_indices.size() < 3) {
      return 0;
    }
    return _indices.size() / 3;
  }
  */
}
