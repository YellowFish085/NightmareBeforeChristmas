#include "projet/default_assimp_mesh.hpp"

using namespace glimac;

namespace Projet
{
	/**
	 * Mesh::MeshEntry::MeshEntry
	 * Constructeur de la struct MeshEntry
	 * Initialise les valeures de la struct avec des valeurs par défaut
	 **/
	Mesh::MeshEntry::MeshEntry()
	{
		NumIndices  = 0;
		MaterialIndex = INVALID_MATERIAL;
	};

	/**
	 * Mesh::MeshEntry::~MeshEntry
	 * Destructeur de la struct MeshEntry
	 **/
	Mesh::MeshEntry::~MeshEntry()
	{
		if (VB != INVALID_OGL_VALUE)
		{
			glDeleteBuffers(1, &VB);
		}

		if (IB != INVALID_OGL_VALUE)
		{
			glDeleteBuffers(1, &IB);
		}
	}

	/**
	 * Mesh::MeshEntry::Init
	 * in vertices Vecteur contenant les sommets du maillage
	 * in indices  Vecteur contenant les indices des sommets pour les faces
	 * Créé les buffers pour les sommets et les faces.
	 **/
	void Mesh::MeshEntry::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		NumIndices = indices.size();

		glGenBuffers(1, &VB);
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &indices[0], GL_STATIC_DRAW);
	}

	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{
		Clear();
	}
	
	void Mesh::Clear()
	{
		for (unsigned int i = 0; i < m_Textures.size(); i++) {
			glDeleteTextures(1, &m_Textures[i]);

		}
	}

	/**
	 * Mesh::LoadMesh
	 * in  filename Chemin du fichier à charger
	 * out  
	 * Charge un fichier 3D.
	 **/
	bool Mesh::LoadMesh(const char* filename)
	{
		// Release the previously loaded mesh (if it exists)
		Clear();

		bool ret = false;
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (pScene) {
		  ret = InitFromScene(pScene, filename);
		}
		else {
		  printf("Error parsing '%s': '%s'\n", filename, importer.GetErrorString());
		}

		return ret;
	}

	/**
	 * Mesh::InitFromScene
	 * in  pScene Variable contenant toutes les informations du fichier 3D chargé
	 * in  filename Chemin du fichier chargé
	 * out 
	 * Initialise l'objet Mesh
	 **/
	bool Mesh::InitFromScene(const aiScene* pScene, const char* filename)
	{
		// On définit l'espace occupé par les vecteurs m_Entries et m_Textures
		// en fonction du nombre de meshes et textures contenues dans l'objet chargé
		m_Entries.resize(pScene->mNumMeshes);
		m_Textures.resize(pScene->mNumMaterials);

		// Initialise les maillages de la scène un par un
		for (unsigned int i = 0; i < m_Entries.size(); i++) {
			const aiMesh* tmpMesh = pScene->mMeshes[i];
			InitMesh(i, tmpMesh);
		}

		return InitMaterials(pScene, filename);
	}

	/**
	 * Mesh::InitMesh
	 * in index Index du maillage traité
	 * in paiMesh Maillage traité
	 * Initialise une struct MeshEntry dans le vecteur m_Entries pour un maillage donné
	 **/
	void Mesh::InitMesh(unsigned int index, const aiMesh* paiMesh)
	{
		// On stocke l'indice du matériau (=texture) associé au maillage courant
		m_Entries[index].MaterialIndex = paiMesh->mMaterialIndex;

		// Vecteur contenant tous les points du maillage
		std::vector<Vertex> vertices;
		// Vecteur contenant toutes les faces du maillage
		std::vector<unsigned int> indices;

		// Valeur par défaut pour la normale ou les coordonées des textures
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		// On stocke dans vertices chaque point du maillage
    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
    		// Position du sommet
				const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
				// Normale du sommet, initialisé à 0,0,0 si absent
				const aiVector3D* pNormal   = &(paiMesh->mNormals[i]) ? &(paiMesh->mNormals[i]) : &Zero3D;
				// Coordonées des textures au sommet, initialisé à 0,0,0 si absent
				const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
                glm::vec2(pTexCoord->x, pTexCoord->y),
                glm::vec3(pNormal->x, pNormal->y, pNormal->z));

        vertices.push_back(v);
    }

    // On stocke dans indices les informations sur les faces du maillage
    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

    // Initialisation de la structure MeshEntry contenu dans le vecteur m_Entries, avec les vecteurs de sommets et d'indices
    m_Entries[index].Init(vertices, indices);
	}

	/**
	 * Mesh::InitMaterials
	 * in  pScene Variable contenant toutes les informations du fichier 3D chargé
	 * in  filename Chemin du fichier chargé
	 *
	 * Charge toutes les textures utilisées par un modèle
	 **/
	bool Mesh::InitMaterials(const aiScene* pScene, const char* filename)
	{
		bool ret = true;
		
		FilePath applicationPath( filename );
		
		// Chargement de la texture par défaut
		std::unique_ptr<Image> defaultTex = loadImage( applicationPath.dirPath() + "white.png" );

		if (defaultTex == NULL) {
			std::cout << "Erreur lors du chargement de la texture par défaut." << std::endl;
			ret = false;
		}

		// On prépare toutes les textures
		for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
			const aiMaterial* pMaterial = pScene->mMaterials[i];

			m_Textures[i] = 0;

			// On ne récupère que les textures diffuses
			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString path;

				// On récupère la texture
				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
					std::unique_ptr<Image> tex = loadImage( applicationPath.dirPath() + path.data );

					GLuint TextureId;
					glGenTextures(1, &TextureId);
					glBindTexture(GL_TEXTURE_2D, TextureId);

					// Si la texture n'a pas pu être chargée, on utilise celle par défaut
					if (tex == NULL){
						std::cout << "Erreur lors du chargement de la texture " << applicationPath.dirPath() + path.data << std::endl;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, defaultTex->getWidth(), defaultTex->getHeight(), 0, GL_RGBA, GL_FLOAT, defaultTex->getPixels());						
						ret = false;
					} else {
						std::cout << "Texture " << applicationPath.dirPath() + path.data << " bien chargée" << std::endl;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->getWidth(), tex->getHeight(), 0, GL_RGBA, GL_FLOAT, tex->getPixels());
					}

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					m_Textures[i] = TextureId;

				}
			}
		}

		return ret;
	}

	void Mesh::Render()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		for (unsigned int i = 0; i < m_Entries.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

			const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

			if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
				glBindTexture(GL_TEXTURE_2D, m_Textures[MaterialIndex]);
			}

			glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}