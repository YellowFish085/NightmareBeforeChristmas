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
		// Initialize SDL and Opengl
		// Exit the app if something went wrong
		if (!initSdlOpenGl()) {
			std::cerr << "Erreur lors de l'initialisation de SDL et OpenGL." << std::endl;
			return false;
		}

		// Initialize the shader program
		// Exit the app if something went wrong
		_Program = new ShaderProgram(_ApplicationPath);
		if (!_Program->init(vsFilename, fsFilename)) {
			std::cerr << "Erreur lors de l'initialisation du ShaderProgram." << std::endl;
			return false;
		}

		// A RETIRER UNE FOIS L'OBJET SCENE FINI
		/*Mesh* mesh = new Mesh(_ApplicationPath);
		if (mesh->loadMesh("Content/box.obj")) {
			std::cout << "Mesh - initalisée correctement." << std::endl;

			glm::mat4 pMatrix, wMatrix, nMatrix;

			pMatrix  = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
			wMatrix = glm::translate(wMatrix, glm::vec3(0, 0, -5));
			nMatrix  = glm::transpose(glm::inverse(wMatrix));

			_Program->setTextureLocation(0);
			_Program->setProjectionMatrix( glm::value_ptr(pMatrix * wMatrix) );
			_Program->setWorldMatrix( glm::value_ptr(wMatrix) );
			_Program->setNormalMatrix( glm::value_ptr(wMatrix) );

			mesh->render();*/

			Scene scene(_ApplicationPath, _Program);

			scene.init("scenes/scene1.json");

			scene.render();

			_WindowManager->swapBuffers();

			getchar(); // juste la pour stoper l'app
			// FIN A RETIRER
		//}
		/*else {
			std::cerr << "Mesh pas ok :c" << std::endl;
		}*/

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
		std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl << std::endl;

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
