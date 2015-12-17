#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <assimp/scene.h>
#include <json/json.h>

#include <glimac/FilePath.hpp>

#include "Mesh.hpp"
#include "shader.hpp"
#include "TrackballCamera.hpp"

namespace Projet
{
	class Scene
	{
		private:
			const glimac::FilePath* _ApplicationPath;
			ShaderProgram* _Program;
			std::vector<Mesh*> _Meshes;
			TrackballCamera _Camera;


		public:
			Scene(const glimac::FilePath* applicationPath, ShaderProgram* program);
			~Scene();

			bool init(const char* sceneFilePath);		// Initialize the scene
			void render();													// Render each meshes
	};
}
