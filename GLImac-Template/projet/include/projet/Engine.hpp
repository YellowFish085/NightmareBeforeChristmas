#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include <json/json.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include "Shader.hpp"
#include "Scene.hpp"


namespace Projet
{
	/**
	 * Class AppEngine
	 * Create a global class that will handle the application
	 **/
	class AppEngine
	{
	public:
		AppEngine(const char* appPath);
		~AppEngine();

		bool init(const char* vsFilename, const char* fsFilename);	// Initialize the components of the app
		void run();																									// Render loop

	private:
		bool initSdlOpenGl();										// Initalize SDL and OpenGl
		bool initScenes(const char* filename);	// Initialize the scenes
		void renderScene();											// Render the current scene
		bool keyboardEvents();									// Keyboard event (return value for alt+f4)
		void mouseEvents();											// Mouse events

		glimac::FilePath* _ApplicationPath;
		glimac::SDLWindowManager* _WindowManager;
		ShaderProgram* _Program;
		std::vector<Scene*> _Scenes;
		int _SceneId;
	};
}
