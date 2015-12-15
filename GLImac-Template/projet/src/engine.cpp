#include "projet/engine.hpp"

namespace Projet
{
	AppEngine::AppEngine(const char* appPath)
	{
		glimac::FilePath* applicationPath = new glimac::FilePath(appPath);
		_ApplicationPath = applicationPath;
	}

	AppEngine::~AppEngine()
	{

	}

	bool AppEngine::init(const char* vsFilename, const char* fsFilename)
	{
		if (!initSdlOpenGl()) {
			std::cerr << "Erreur lors de l'initialisation de SDL et OpenGL." << std::endl;
			return false;
		}

		_Program = new ShaderProgram(_ApplicationPath);
		if (!_Program->init(vsFilename, fsFilename)) {
			std::cerr << "Erreur lors de l'initialisation du ShaderProgram." << std::endl;
			return false;
		}

		return true;
	}

	bool AppEngine::initSdlOpenGl()
	{
		std::cout << "SDL et OpenGl - initialisation..." << std::endl;

		glimac::SDLWindowManager* windowManager = new glimac::SDLWindowManager(800, 600, "Nightmare Before Christmas");
		
		if (!windowManager) {
			return false;
		}
		
		_WindowManager = windowManager;

		GLenum glewInitError = glewInit();

		if (GLEW_OK != glewInitError) {
			std::cerr << glewGetErrorString(glewInitError) << std::endl;
			return false;
		}

		std::cout << "SDL et OpenGl - initialisés correctement." << std::endl;
		std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

		return true;
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