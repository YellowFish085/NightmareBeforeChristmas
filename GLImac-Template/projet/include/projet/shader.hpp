#pragma once

#include <iostream>
#include <string.h>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

namespace Projet
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const glimac::FilePath* applicationPath);
		~ShaderProgram();

		bool init(const char* vsFilename, const char* fsFilename);
		void use();

	private:
		const glimac::FilePath** _ApplicationPath;	// Pour le chemin de chargement des shaders
		glimac::Program _Program;						// Programme glimac
		GLint _MVPlocation;									// Model View Projetction matrix location
		GLint _MVlocation;									// Model View matrix location
		GLint _Nlocation;										// Normal matrix location
	};
}