#pragma once

#include <iostream>
#include <string.h>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

namespace Projet
{
	/**
	 * Class ShaderProgram
	 * Create the shader program which will be used in the app
	 **/
	class ShaderProgram
	{
	public:
		ShaderProgram(const glimac::FilePath* applicationPath);
		~ShaderProgram();

		bool init(const char* vsFilename, const char* fsFilename);	// Create a shader program
		void use();																									// Use the shader program

		// Setters for the uniforms variables
		void setTextureLocation(unsigned int v);
		void setProjectionMatrix(const float* v);
		void setWorldMatrix(const float* v);
		void setNormalMatrix(const float* v);
		
	private:
		GLint _Texlocation;	// Texture location
		GLint _PMlocation;	// Projection Matrix location
		GLint _WMlocation;	// World Matrix location
		GLint _NMlocation;	// Normal Matrix location

		const glimac::FilePath** _ApplicationPath;
		glimac::Program _Program;
	};
}