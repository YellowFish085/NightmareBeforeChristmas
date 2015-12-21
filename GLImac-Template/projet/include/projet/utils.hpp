#pragma once

#include <glimac/FilePath.hpp>

namespace Projet
{
	extern glimac::FilePath* gApplicationPath;

	void initApplicationPath(const char* argv);
}