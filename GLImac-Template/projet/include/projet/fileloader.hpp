#pragma once

#include <stdlib.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Projet
{
	const aiScene* loadScene( const char* filename );
}