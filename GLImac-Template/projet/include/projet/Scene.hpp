#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <assimp/scene.h>
#include <json/json.h>

#include <glimac/FilePath.hpp>

#include "utils.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TrackballCamera.hpp"

namespace Projet
{
	class Scene
	{
		private:
			ShaderProgram* _Program;
			std::vector<Mesh*> _Meshes;
			TrackballCamera _Camera;


		public:
			Scene(ShaderProgram* program);
			~Scene();

			bool init(const char* sceneFilePath);		// Initialize the scene
			void render();													// Render each meshes
	};
}
