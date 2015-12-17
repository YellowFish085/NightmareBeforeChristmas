#pragma once
#include <glimac/glm.hpp>

namespace Projet
{
	class TrackballCamera
	{

		/* ATTRIBUTS */
		private :
			float m_fDistance;
			float m_fAngleX;
			float m_fAngleY;

		/* METHODES */
		/* contstructeurs */
		public :
			TrackballCamera();

			TrackballCamera(float distance, float angleX, float angleY);

			TrackballCamera(const TrackballCamera& rhs);

		/* Autres */
		void moveFront(float delta);

		void rotateLeft(float degrees);

		void rotateUp(float degrees);

		glm::mat4 getViewMatrix() const;

	};
}
