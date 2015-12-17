#pragma once

#include <iostream>
#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include "shader.hpp"
#include "Mesh.hpp" // Sans doute à retirer une fois que l'objet scene sera fait
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
		void renderScene();
		void keyboardEvents();
		void mouseEvents();

		glimac::FilePath* _ApplicationPath;
		glimac::SDLWindowManager* _WindowManager;
		ShaderProgram* _Program;
	};
}
