#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include <json/json.h>

#include "shader.hpp"
#include "scene.hpp"


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

		// Initialize the components of the app
		bool init(const char* vsFilename, const char* fsFilename);
		void run();

	private:
		bool initSdlOpenGl();		// Initalize SDL and OpenGl
		bool initScenes(const char* filename);
		void renderScene();
		void keyboardEvents();
		void mouseEvents();

		glimac::FilePath* _ApplicationPath;
		glimac::SDLWindowManager* _WindowManager;
		ShaderProgram* _Program;
		std::vector<Scene*> _Scenes;
	};
}
