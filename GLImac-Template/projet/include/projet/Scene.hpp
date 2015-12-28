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
#include "Light.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

namespace Projet
{
	class Scene
	{
		private:
			ShaderProgram* _Program;
			std::vector<Mesh*> _Meshes;
			std::vector<Light*> _Lights;


		public:
			TrackballCamera _Camera;

			Scene(ShaderProgram* program);
			~Scene();

			bool init(const char* sceneFilePath);		// Initialize the scene
			void render();													// Render each meshes
	};
}
