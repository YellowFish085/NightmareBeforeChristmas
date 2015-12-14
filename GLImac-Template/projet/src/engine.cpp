#include "projet/engine.hpp"

namespace Projet
{
	AppEngine::AppEngine(const char* appPath)
	{
		glimac::FilePath applicationPath(appPath);
		_ApplicationPath = applicationPath;
	}

	AppEngine::~AppEngine()
	{

	}

	bool AppEngine::init(const char* vsFilename, const char* fsFilename)
	{
		_Program = new ShaderProgram(_ApplicationPath);
		_Program->init(vsFilename, fsFilename);
	}

	void AppEngine::run()
	{

	}

	void AppEngine::renderScene()
	{

	}

	void AppEngine::keyboardEvents()
	{

	}

	void AppEngine::mouseEvents()
	{
		
	}
}