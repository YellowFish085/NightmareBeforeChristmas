#include "projet/Engine.hpp"

namespace Projet
{
	AppEngine::AppEngine(const char* appPath)
	{
		_SceneId = -1;

		initApplicationPath(appPath);
		std::cout << "App run on " << gApplicationPath->dirPath() << std::endl;
	}

	AppEngine::~AppEngine()
	{

	}

	bool AppEngine::init(const char* vsFilename, const char* fsFilename)
	{
		std::cout << std::endl << "*********************************************" << std::endl;
		std::cout << "Début de l'initialisation de l'application." << std::endl << std::endl;

		// Initialize SDL and Opengl
		// Exit the app if something went wrong
		if (!initSdlOpenGl()) {
			std::cerr << "ERROR: Erreur lors de l'initialisation de SDL et OpenGL." << std::endl;
			return false;
		}

		// Initialize the shader program
		// Exit the app if something went wrong
		_Program = new ShaderProgram();
		if (!_Program->init(vsFilename, fsFilename)) {
			std::cerr << "ERROR: Erreur lors de l'initialisation du ShaderProgram." << std::endl;
			return false;
		}

		// Initialize the scenes
		// Exit the app if something went wrong
		if (!initScenes("scenes/scenesList.json")) {
			std::cerr << "ERROR: Erreur lors de l'initialisation des scènes." << std::endl;
			return false;
		}

		_SceneId = 0;

		std::cout << "Fin de l'initialisation de l'application." << std::endl;
		std::cout << "*********************************************" << std::endl;

		return true;
	}

	bool AppEngine::initSdlOpenGl()
	{
		std::cout << "====" << std::endl << "SDL et OpenGl - initialisation..." << std::endl;

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
		std::cout << "====" << std::endl << "Scenes - initialisation..." << std::endl;

		// A json file with the scenes is loaded
		std::ifstream sceneList(getScenesFilePath(filename), std::ios::in);

		if (!sceneList) {
			std::cerr << "ERROR: Impossible d'ouvrir le fichier contenant la liste des scènes " << getScenesFilePath(filename) << std::endl;
			return false;
		}
		std::cout << "Liste des scenes ouvert..." << std::endl;

		// Retrieve the root node
		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneList, root, false)) {
      std::cerr  << "ERROR: Erreur lors de la récupération du json !" << std::endl;
			return false;
		}

		// retrieve the "scenes" node
		const Json::Value scenes = root["scenes"];
		if (scenes == 0) {
			std::cerr << "ERROR: Impossible de récupérer le noeud scenes !" << std::endl;
			return false;
		}

		// Initalize each scene
		for (int i = 0; i < scenes.size(); i++) {
			std::cout << std::endl << scenes[i].get("name", 0).asString() << " - initialisation..." << std::endl;

			Scene* tmp = new Scene(_Program);

			if ( tmp->init(scenes[i].get("source", 0).asString().c_str()) ) {
				_Scenes.push_back(tmp);
			}
			else {
				std::cerr << "ERROR: Scene " << scenes[i].get("source", 0) << " n'a pas pu être initialisée." << std::endl;
				return false;
			}
		}

		std::cout << std::endl << "Scenes - initialisées correctement." << std::endl << std::endl;

		return true;
	}

	void AppEngine::run()
	{
		std::cout << std::endl << "App run..." << std::endl;

		bool done = false;

		while(!done) {
			if (keyboardEvents()) {
				done = true;
			}

			mouseEvents();

			renderScene();
		}

		std::cout << std::endl << "App run fin." << std::endl;
	}

	void AppEngine::renderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_Scenes[_SceneId]->render();
		_WindowManager->swapBuffers();
	}

	bool AppEngine::keyboardEvents()
	{
		SDL_Event e;

		while(_WindowManager->pollEvent(e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_LEFT:
						_SceneId = ((_SceneId <= 0) ? 0 : _SceneId-1);
						break;
					case SDLK_RIGHT:
						_SceneId = ((_SceneId >= _Scenes.size()-1) ? _SceneId : _SceneId+1);
						break;
				}

				std::cout << _SceneId << std::endl;
			}

			if(e.type == SDL_QUIT) {
				std::cout << std::endl << "Fermeture d'application reçue..." << std::endl;
				return true;
			}
			else {
				return false;
			}
		}
	}

	void AppEngine::mouseEvents()
	{
		SDL_Event e;

		while(_WindowManager->pollEvent(e))
		{

			if (e.type == SDL_MOUSEMOTION)
			{
			    if (e.motion.state & SDL_BUTTON_LMASK)
			    {
						_Scenes[_SceneId]->_Camera.rotateLeft((float)e.motion.xrel);
						_Scenes[_SceneId]->_Camera.rotateUp((float)e.motion.yrel);
			    }
					else if (e.motion.state & SDL_BUTTON_RMASK)
			    {
						_Scenes[_SceneId]->_Camera.moveFront((float)-e.motion.yrel*0.05);
			    }
			}
		}
	}
}
