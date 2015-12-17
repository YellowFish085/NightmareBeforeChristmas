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

		if (!initScenes("scenes/scenesList.json")) {
			std::cerr << "Erreur lors de l'initialisation des scènes." << std::endl;
		}
		else {
			std::cout << "Scenes bien chargées yolo" << std::endl;
			_Scenes[0]->render();
			_WindowManager->swapBuffers();
			getchar();
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
		std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl << std::endl;

		return true;
	}

	bool AppEngine::initScenes(const char* filename)
	{
		std::cout << "Scenes - initialisation..." << std::endl;

		std::ifstream sceneList((_ApplicationPath->dirPath() + "/../assets/" + filename).c_str(), std::ios::in);

		if (!sceneList) {
			std::cerr << "Impossible d'ouvrir le fichier contenant la liste des scènes " << (_ApplicationPath->dirPath() + "/../assets/" + filename).c_str() << std::endl;
			return false;
		}
		else {
			std::cout << "Liste des scenes bien chargée..." << std::endl;
		}

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneList, root, false)) {
      std::cerr  << "Erreur lors de la récupération du json !" << std::endl;
			return false;
		}

		const Json::Value scenes = root["scenes"];
		if (scenes == 0) {
			std::cerr << "Impossible de récupérer le noeud scenes !" << std::endl;
			return false;
		}

		for (int i = 0; i < scenes.size(); i++) {
			Scene* tmp = new Scene(_ApplicationPath, _Program);

			if ( scenes[i].get("source", 0).asString().c_str() && tmp->init(scenes[i].get("source", 0).asString().c_str()) ) {
				_Scenes.push_back(tmp);
			}
			else {
				std::cerr << "Scene " << scenes[i].get("source", 0) << " n'a pas pu être initialisée." << std::endl;
				return false;
			}
		}

		std::cout << "Scenes - initialisées correctement." << std::endl << std::endl;

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
