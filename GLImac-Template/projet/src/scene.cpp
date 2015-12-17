#include "projet/scene.hpp"

namespace Projet
{

	/* CONSTRUCTORS */
	/* Default */
	Scene::Scene(const glimac::FilePath* applicationPath, ShaderProgram* program):
		_applicationPath(applicationPath),
		_program(program),
		_camera(TrackballCamera())
	{};

	/* DESTRUCTOR */
	Scene::~Scene() {
		for (auto mesh = _meshes.begin(); mesh != _meshes.end(); ++mesh) {
			delete(*mesh);
		}
	}

	/* INIT */
	void Scene::init(const char* sceneFilePath)
	{
		std::ifstream sceneFile((_applicationPath->dirPath() + "/../assets/" + sceneFilePath).c_str(), std::ios::in);

		if (!sceneFile) {
			std::cerr << "Impossible d'ouvrir le fichier de scene  à l'adresse : " << (_applicationPath->dirPath() + "/../assets/" + sceneFilePath).c_str() << std::endl;
			return;
		}
		else {
			std::cout << "Fichier de scene ouvert" << std::endl;
			std::cout << sceneFile << std::endl;
		}

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneFile, root, false)) {
			// report to the user the failure and their locations in the document.
      std::cerr  << "Erreur lors de la récupération du json !" << std::endl;
			return;
		}

		std::cout << "type: " << root.type() << std::endl;

		const Json::Value meshes = root["meshes"]; // Get the meshes node
		if (meshes == 0) {
			std::cerr << "Impossible de récupérer le noeud meshes !" << std::endl;
			return;
		}

		for (int i = 0; i < meshes.size(); i++) {
			std::cout << i << std::endl;
			Mesh* tmpMesh = new Mesh(_applicationPath);

			if (tmpMesh->loadMesh(meshes[i].get("source", 0).asString().c_str())) {
				std::cout << "Mesh - initalisée correctement." << std::endl;
			}

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

			_meshes.push_back(tmpMesh);

		}

		const Json::Value cameraDatas = root["camera"]; // Get the camera node
		if (cameraDatas == 0) {
			std::cerr << "Impossible de récupérer le noeud camera !" << std::endl;
			return;
		}

		_camera = TrackballCamera(
			cameraDatas.get("distanceToCenter", 5).asFloat(),
			cameraDatas.get("angle",0).get("x",0).asFloat(),
			cameraDatas.get("angle",0).get("y",0).asFloat()
		);

	}

	void Scene::render() {
		glEnable(GL_DEPTH_TEST);
		for (auto mesh = _meshes.begin(); mesh != _meshes.end(); ++mesh) {
			glm::mat4 MVMatrix, ProjMatrix, NormalMatrix, ViewMatrix;

			MVMatrix = glm::translate(glm::mat4(1), (*mesh)->_position);
			MVMatrix = glm::rotate(MVMatrix, glm::radians((*mesh)->_angle), (*mesh)->_rotAxe);
			MVMatrix = glm::scale(MVMatrix, (*mesh)->_scale);

			ViewMatrix = _camera.getViewMatrix();

			MVMatrix = ViewMatrix * MVMatrix;

			ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

			NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

			std::cout << "addresse scene" << _program << std::endl;

			_program->setTextureLocation(0);
			_program->setProjectionMatrix( glm::value_ptr(ProjMatrix * MVMatrix) );
			_program->setWorldMatrix( glm::value_ptr(MVMatrix) );
			_program->setNormalMatrix( glm::value_ptr(MVMatrix) );

			(*mesh)->render();
		}
	}
}
