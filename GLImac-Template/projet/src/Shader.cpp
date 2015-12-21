#include "projet/Shader.hpp"

namespace Projet
{
	ShaderProgram::ShaderProgram()
	{
	}

	ShaderProgram::~ShaderProgram()
	{

	}

	bool ShaderProgram::init(const char* vsFilename, const char* fsFilename)
	{
		std::cout << "=====" << std::endl << "ShaderProgram - initialisation..." << std::endl;

		glimac::FilePath vsPath, fsPath;
		getShaderFilePath(&vsPath, vsFilename);
		getShaderFilePath(&fsPath, fsFilename);

		_Program = loadProgram(vsPath, fsPath);

		use();

		_Texlocation = glGetUniformLocation(_Program.getGLId(), "uTexture");
		_PMlocation  = glGetUniformLocation(_Program.getGLId(), "uPMatrix");
		_WMlocation  = glGetUniformLocation(_Program.getGLId(), "uWMatrix");
		_NMlocation  = glGetUniformLocation(_Program.getGLId(), "uNMatrix");
		
		std::cout << "ShaderProgram - créé avec succès. " << std::endl << std::endl;

		return true;
	}

	void ShaderProgram::use()
	{
		_Program.use();
	}

	void ShaderProgram::setTextureLocation(unsigned int v)
	{
	  glUniform1i(_Texlocation, v);
	}

	void ShaderProgram::setProjectionMatrix(const float* v)
	{
		glUniformMatrix4fv(_PMlocation, 1, GL_FALSE, v);
	}

	void ShaderProgram::setWorldMatrix(const float* v)
	{
		glUniformMatrix4fv(_WMlocation, 1, GL_FALSE, v);
	}

	void ShaderProgram::setNormalMatrix(const float* v)
	{
		glUniformMatrix4fv(_NMlocation, 1, GL_FALSE, v);
	}
}