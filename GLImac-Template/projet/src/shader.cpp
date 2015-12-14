#include "projet/shader.hpp"

namespace Projet
{
	ShaderProgram::ShaderProgram(const glimac::FilePath applicationPath)
	{
		_applicationPath = applicationPath;
	}

	ShaderProgram::~ShaderProgram()
	{

	}

	bool ShaderProgram::init(const char* vsFilename, const char* fsFilename)
	{
		_Program = loadProgram(
				_applicationPath.dirPath() + "shaders/" + vsFilename,
				_applicationPath.dirPath() + "shaders/" + fsFilename);

		use();

		_MVPlocation = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
		_MVlocation = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
		_Nlocation = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");

		std::cout << "Shader Program créé avec succès. " << std::endl;

		return true;
	}

	void ShaderProgram::use()
	{
		_Program.use();
	}
}