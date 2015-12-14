#pragma once

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
		void renderScene();
		void keyboardEvents();
		void mouseEvents();

	private:
		glimac::FilePath _ApplicationPath;
		ShaderProgram* _Program;
	};
}