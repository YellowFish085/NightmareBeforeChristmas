#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <assimp/scene.h>

#include <glimac/FilePath.hpp>

#include <json/json.h>

#include "Mesh.hpp"
#include "shader.hpp"
#include "TrackballCamera.hpp"

namespace Projet
{
	class Scene
	{

		/* ATTRIBUTES */
		private:
			std::vector<Mesh*> _meshes;
			const glimac::FilePath* _applicationPath;
			ShaderProgram* _program;
			TrackballCamera _camera;


		public:
			/* CONSTRUCTORS */
			/* Default */
			Scene(const glimac::FilePath* applicationPath, ShaderProgram* program);

			/* DESTRUCTOR */
			~Scene();

			/* INIT */
			void init(const char* sceneFilePath);

			/* RENDER */
			void render();
	};
}
