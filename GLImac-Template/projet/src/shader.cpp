#include "projet/shader.hpp"

namespace Projet
{
	ShaderProgram::ShaderProgram(const glimac::FilePath* applicationPath)
	{
		_ApplicationPath = &applicationPath;
	}

	ShaderProgram::~ShaderProgram()
	{

	}

	bool ShaderProgram::init(const char* vsFilename, const char* fsFilename)
	{
		std::cout << "ShaderProgram - initialisation..." << std::endl;

		const glimac::FilePath* dir = *_ApplicationPath;

		_Program = loadProgram(
				dir->dirPath() + "shaders/" + vsFilename,
				dir->dirPath() + "shaders/" + fsFilename);

		use();

		_MVPlocation = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
		_MVlocation = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
		_Nlocation = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");

		std::cout << "ShaderProgram - créé avec succès. " << std::endl;

		return true;
	}

	void ShaderProgram::use()
	{
		_Program.use();
	}
}