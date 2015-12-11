#include "projet/fileloader.hpp"

namespace Projet
{
	const aiScene* loadScene( const char* filename )
	{
		std::cout << "Ouverture du fichier " << filename << std::endl;
		
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile( filename, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

		if( !scene ) {
			std::cout << "ERROR    Fichier " << filename << " n'a pas été ouvert." << std::endl;
			exit(EXIT_FAILURE);
		}	else {
			std::cout << "OK    Fichier " << filename << " ouvert correctement." << std::endl;
			return scene;
		}
	}
}