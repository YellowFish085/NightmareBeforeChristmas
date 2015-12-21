#include "projet/utils.hpp"

namespace Projet
{
	#define RELATIVE_ASSETS_PATH "/../assets/"
	#define RELATIVE_CONTENT_PATH "content/"
	#define RELATIVE_SHADERS_PATH "/shaders/"

	glimac::FilePath* gApplicationPath;

	void initApplicationPath(const char* argv)
	{
		gApplicationPath = new glimac::FilePath(argv);
	}

}