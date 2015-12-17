#include "projet/Scene.hpp"

namespace Projet
{
	Scene::Scene(const glimac::FilePath* applicationPath, ShaderProgram* program):
		_ApplicationPath(applicationPath),
		_Program(program),
		_Camera(TrackballCamera())
	{};

	Scene::~Scene() {
		for (auto mesh = _Meshes.begin(); mesh != _Meshes.end(); ++mesh) {
			delete(*mesh);
		}
	}

	bool Scene::init(const char* sceneFilePath)
	{
		// Load the json with the scene datas
		std::ifstream sceneFile((_ApplicationPath->dirPath() + "/../assets/" + sceneFilePath).c_str(), std::ios::in);

		if (!sceneFile) {
			std::cerr << "- Impossible d'ouvrir le fichier de scene  à l'adresse : " << (_ApplicationPath->dirPath() + "/../assets/" + sceneFilePath).c_str() << std::endl;
			return false;
		}
		std::cout << "- Fichier " << sceneFilePath << " ouvert..." << std::endl;

		// Retrieve the root node
		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneFile, root, false)) {
      std::cerr  << "- Erreur lors de la récupération du json !" << std::endl;
			return false;
		}

		// Retrieve the "meshes" node
		const Json::Value meshes = root["meshes"];
		if (meshes == 0) {
			std::cerr << "- Impossible de récupérer le noeud meshes !" << std::endl;
			return false;
		}

		// Initialize each mesh
		for (int i = 0; i < meshes.size(); i++) {
			std::cout << "- Mesh " << i+1 << " sur " << meshes.size() << " - initialisation..." << std::endl;

			Mesh* tmpMesh = new Mesh(_ApplicationPath);

			// Initialize the mesh
			if (tmpMesh->loadMesh(meshes[i].get("source", 0).asString().c_str())) {
				std::cout << "- Mesh " << i+1 << " initalisée correctement." << std::endl;
			}

			// Set the relative coords, rotation and scale of the mesh
			tmpMesh->setPosition(glm::vec3(
				meshes[i].get("position",0).get("x",0).asFloat(),
				meshes[i].get("position",0).get("y",0).asFloat(),
				meshes[i].get("position",0).get("z",0).asFloat()
			));

			tmpMesh->setAngle(meshes[i].get("rotation",0).asFloat());
			tmpMesh->setRotAxe(glm::vec3(
				meshes[i].get("axis",0).get("x",0).asFloat(),
				meshes[i].get("axis",0).get("y",1).asFloat(),
				meshes[i].get("axis",0).get("z",0).asFloat()
			));

			tmpMesh->setScale(glm::vec3(
				meshes[i].get("scale",0).get("x",1).asFloat(),
				meshes[i].get("scale",0).get("y",1).asFloat(),
				meshes[i].get("scale",0).get("z",1).asFloat()
			));

			_Meshes.push_back(tmpMesh);

		}

		// Retrieve the camera node, used to set the défault caméra
		const Json::Value cameraDatas = root["camera"];
		if (cameraDatas == 0) {
			std::cerr << "- Impossible de récupérer le noeud camera !" << std::endl;
			return false;
		}

		// Initialize the camera
		_Camera = TrackballCamera(
			cameraDatas.get("distanceToCenter", 5).asFloat(),
			cameraDatas.get("angle",0).get("x",0).asFloat(),
			cameraDatas.get("angle",0).get("y",0).asFloat()
		);

		return true;

	}

	void Scene::render() {
		glEnable(GL_DEPTH_TEST);

		// Render each mesh
		for (auto mesh = _Meshes.begin(); mesh != _Meshes.end(); ++mesh) {
			glm::mat4 MVMatrix, ProjMatrix, NormalMatrix, ViewMatrix;

			MVMatrix = glm::translate(glm::mat4(1), (*mesh)->_position);
			MVMatrix = glm::rotate(MVMatrix, glm::radians((*mesh)->_angle), (*mesh)->_rotAxe);
			MVMatrix = glm::scale(MVMatrix, (*mesh)->_scale);

			ViewMatrix = _Camera.getViewMatrix();

			MVMatrix = ViewMatrix * MVMatrix;

			ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

			NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

			_Program->setTextureLocation(0);
			_Program->setProjectionMatrix( glm::value_ptr(ProjMatrix * MVMatrix) );
			_Program->setWorldMatrix( glm::value_ptr(MVMatrix) );
			_Program->setNormalMatrix( glm::value_ptr(MVMatrix) );

			(*mesh)->render();
		}
	}
}
