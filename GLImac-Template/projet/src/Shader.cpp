#include "projet/Shader.hpp"

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
		std::cout << "=====" << std::endl << "ShaderProgram - initialisation..." << std::endl;

		const glimac::FilePath* dir = *_ApplicationPath;

		_Program = loadProgram(
				dir->dirPath() + "shaders/" + vsFilename,
				dir->dirPath() + "shaders/" + fsFilename);

		use();

		_Texlocation = glGetUniformLocation(_Program.getGLId(), "uTexture");
		_PMlocation  = glGetUniformLocation(_Program.getGLId(), "uPMatrix");
		_WMlocation  = glGetUniformLocation(_Program.getGLId(), "uWMatrix");
		_NMlocation  = glGetUniformLocation(_Program.getGLId(), "uNMatrix");

		_diffuseLocation = glGetUniformLocation(_Program.getGLId(), "uKd");
		_specularLocation = glGetUniformLocation(_Program.getGLId(), "uKs");
		_shininessLocation = glGetUniformLocation(_Program.getGLId(), "uShininess");

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

	void ShaderProgram::setDiffuse(const glm::vec3 d)
	{
		glUniform3f(_diffuseLocation, d.r, d.g, d.b);
	}

	void ShaderProgram::setSpecular(const glm::vec3 s)
	{
		glUniform3f(_specularLocation, s.r, s.g, s.b);
	}

	void ShaderProgram::setShininess(const float s)
	{
		glUniform1f(_shininessLocation, s);
	}


	void ShaderProgram::setLights(const std::vector<Light*> lights, const glm::mat4* ViewMatrix) {
		GLuint typeLocation;
		GLuint intensityLocation;
		GLuint positionLocation;

		for (int i = 0; i < lights.size(); i++) {
			std::ostringstream typeStr;
			typeStr  << std::string("uLights[") << i << std::string("].type");
			std::ostringstream intensityStr;
			intensityStr <<  std::string("uLights[") << i << std::string("].intensity");
			std::ostringstream positionStr;
			positionStr <<  std::string("uLights[") << i << std::string("].position");

			typeLocation = glGetUniformLocation(_Program.getGLId(), typeStr.str().c_str());
			intensityLocation = glGetUniformLocation(_Program.getGLId(), intensityStr.str().c_str());
			positionLocation = glGetUniformLocation(_Program.getGLId(), positionStr.str().c_str());

			glUniform1i(typeLocation, lights[i]->getType());
			glUniform3f(intensityLocation, lights[i]->getIntensity().r, lights[i]->getIntensity().g, lights[i]->getIntensity().b);

			if(lights[i]->getType() == LIGHT_AMBIENT) {
				glUniform3f(positionLocation, 0, 0, 0);
			}
			else if(lights[i]->getType() == LIGHT_DIRECTIONAL) {
				DirectionalLight* tmpLight = dynamic_cast<DirectionalLight*>(lights[i]);
				glm::vec3 direction = glm::vec3(*ViewMatrix * glm::vec4(tmpLight->getDirection(), 0));
				glUniform3f(positionLocation, direction.x, direction.y, direction.z);
			}
			else if(lights[i]->getType() == LIGHT_POINT) {
				PointLight* tmpLight = dynamic_cast<PointLight*>(lights[i]);
				glm::vec3 position = glm::vec3(*ViewMatrix * glm::vec4(tmpLight->getPosition().x, tmpLight->getPosition().y,tmpLight->getPosition().z, 1));
				glUniform3f(positionLocation, position.x, position.y, position.z);
			}
		}

		GLuint nbLightsLocation = glGetUniformLocation(_Program.getGLId(), "uNbLights");
		glUniform1i(nbLightsLocation, lights.size());
	}
}
