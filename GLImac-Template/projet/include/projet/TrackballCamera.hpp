#pragma once
#include <glimac/glm.hpp>

namespace Projet
{
	class TrackballCamera
	{
	private:
		float m_fDistance;
		float m_fAngleX;
		float m_fAngleY;
		float m_maxDistance;
		float m_minDistance;

	public:
		TrackballCamera();
		TrackballCamera(float distance, float min, float max, float angleX, float angleY);
		TrackballCamera(const TrackballCamera& rhs);
		~TrackballCamera();

		void moveFront(float delta);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		glm::mat4 getViewMatrix() const;

	};
}
