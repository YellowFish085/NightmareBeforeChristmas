#include "projet/Scene.hpp"

namespace Projet
{
	Scene::Scene(ShaderProgram* program):
		_Program(program),
		_Camera(TrackballCamera())
	{};

	Scene::~Scene()
	{

	}

	bool Scene::init(const char* sceneFilePath)
	{
		// Load the json with the scene datas
		std::ifstream sceneFile(getScenesFilePath(sceneFilePath), std::ios::in);

		if (!sceneFile) {
			std::cerr << "- ERROR: Impossible d'ouvrir le fichier scene " << getScenesFilePath(sceneFilePath) << std::endl;
			return false;
		}
		std::cout << "- Fichier " << sceneFilePath << " ouvert..." << std::endl;

		// Retrieve the root node
		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneFile, root, false)) {
      std::cerr  << "- ERROR: Erreur lors de la récupération du json !" << std::endl;
			return false;
		}

		// Retrieve the "meshes" node
		const Json::Value meshes = root["meshes"];
		if (meshes == 0) {
			std::cerr << "- ERROR: Impossible de récupérer le noeud meshes !" << std::endl;
			return false;
		}

		// Initialize each mesh
		for (int i = 0; i < meshes.size(); i++) {
			std::cout << "- Mesh " << i+1 << " sur " << meshes.size() << " - initialisation..." << std::endl;

			Mesh* tmpMesh = new Mesh();

			// Initialize the mesh
			if (tmpMesh->loadMesh(meshes[i].get("source", 0).asString().c_str())) {
				std::cout << "- Mesh " << i+1 << " initalisée correctement." << std::endl;
			}
			else {
				std::cerr << "- ERROR: Erreur lors de l'initialisation de la Mesh " << i+1 << std::endl;
				return false;
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

		// Retrieve the "lights" node
		const Json::Value lights = root["lights"];
		if (lights == 0) {
			std::cerr << "- ERROR: Impossible de récupérer le noeud lights !" << std::endl;
			return false;
		}

		for (int i = 0; i < lights.size() && i < 10 ; i++) {
			std::cout << "- Light " << i+1 << " sur " << lights.size() << " - initialisation..." << std::endl;

			if (lights[i].get("type",0).asString() == "ambient") {
				_Lights.push_back( new AmbientLight(glm::vec3(
						lights[i].get("intensity",1).get("r",1).asFloat(),
						lights[i].get("intensity",1).get("g",1).asFloat(),
						lights[i].get("intensity",1).get("b",1).asFloat()
					))
				);
			}
			else if (lights[i].get("type",0).asString() == "directional") {
					std::cout << "-- DirectionalLight" << std::endl;
					_Lights.push_back(new DirectionalLight(glm::vec3(
							lights[i].get("intensity",1).get("r",1).asFloat(),
							lights[i].get("intensity",1).get("g",1).asFloat(),
							lights[i].get("intensity",1).get("b",1).asFloat()
						),
						glm::vec3(
							lights[i].get("direction",0).get("x",0).asFloat(),
							lights[i].get("direction",0).get("y",0).asFloat(),
							lights[i].get("direction",-1).get("z",-1).asFloat()
						)
					)
				);
			}
			else if (lights[i].get("type",0).asString() == "point") {
					_Lights.push_back(new PointLight(glm::vec3(
							lights[i].get("intensity",1).get("r",1).asFloat(),
							lights[i].get("intensity",1).get("g",1).asFloat(),
							lights[i].get("intensity",1).get("b",1).asFloat()
						),
						glm::vec3(
							lights[i].get("position",0).get("x",0).asFloat(),
							lights[i].get("position",0).get("y",0).asFloat(),
							lights[i].get("position",0).get("z",0).asFloat()
						)
					)
				);
			}
		}

		// Retrieve the camera node, used to set the défault caméra
		const Json::Value cameraDatas = root["camera"];
		if (cameraDatas == 0) {
			std::cerr << "- ERROR: Impossible de récupérer le noeud camera !" << std::endl;
			return false;
		}

		// Initialize the camera
		_Camera = TrackballCamera(
			cameraDatas.get("distanceToCenter", 5).get("base", 5).asFloat(),
			cameraDatas.get("distanceToCenter", 5).get("min", 5).asFloat(),
			cameraDatas.get("distanceToCenter", 5).get("max", 5).asFloat(),
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

			MVMatrix = glm::translate(glm::mat4(1), (*mesh)->getPosition());
			MVMatrix = glm::rotate(MVMatrix, glm::radians((*mesh)->getAngle()), (*mesh)->getRotAxe());
			MVMatrix = glm::scale(MVMatrix, (*mesh)->getScale());

			ViewMatrix = _Camera.getViewMatrix();

			MVMatrix = ViewMatrix * MVMatrix;

			ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

			NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

			_Program->setTextureLocation(0);
			_Program->setDiffuse((*mesh)->getDiffuse());
			_Program->setSpecular((*mesh)->getSpecular());
			_Program->setShininess((*mesh)->getShininess());
			_Program->setProjectionMatrix( glm::value_ptr(ProjMatrix * MVMatrix) );
			_Program->setWorldMatrix( glm::value_ptr(MVMatrix) );
			_Program->setNormalMatrix( glm::value_ptr(MVMatrix) );
			_Program->setLights(_Lights, &ViewMatrix);

			(*mesh)->render();
		}
	}
}
