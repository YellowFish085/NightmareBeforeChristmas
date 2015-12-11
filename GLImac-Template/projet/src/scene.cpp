#include "projet/scene.hpp"

namespace Projet
{
	Scene::Scene( const char* filename )
	{
		const aiScene* scene = Projet::loadScene( filename );
	}
}