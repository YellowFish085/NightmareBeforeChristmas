#pragma once

#include <iostream>
#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include "shader.hpp"

namespace Projet
{
	class AppEngine
	{
	public:
		AppEngine(const char* appPath);
		~AppEngine();

		bool init(const char* vsFilename, const char* fsFilename);
		void run();

	private:
		bool initSdlOpenGl();
		void renderScene();
		void keyboardEvents();
		void mouseEvents();
		glimac::FilePath* _ApplicationPath;
		glimac::SDLWindowManager* _WindowManager;
		ShaderProgram* _Program;
	};
}