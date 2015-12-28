#include "projet/TrackballCamera.hpp"

namespace Projet
{
	TrackballCamera::TrackballCamera() :
		m_fDistance(0),
		m_minDistance(0),
		m_maxDistance(10),
		m_fAngleX(0),
		m_fAngleY(0)
	{}

	TrackballCamera::TrackballCamera(float distance, float min, float max, float angleX, float angleY) :
		m_fDistance(distance),
		m_minDistance(min),
		m_maxDistance(max),
		m_fAngleX(angleX),
		m_fAngleY(angleY)
	{}

	TrackballCamera::TrackballCamera(const TrackballCamera& rhs):
		m_fDistance(rhs.m_fDistance),
		m_fAngleX(rhs.m_fAngleX),
		m_fAngleY(rhs.m_fAngleY)
	{}

	TrackballCamera::~TrackballCamera()
	{

	}

	void TrackballCamera::moveFront(float delta)
	{
		m_fDistance += delta;
		if (m_fDistance <= m_minDistance) {
			m_fDistance = m_minDistance;
		}
		else if ( m_fDistance >= m_maxDistance) {
			m_fDistance = m_maxDistance;
		}
	}

	void TrackballCamera::rotateLeft(float degrees)
	{
		m_fAngleX += degrees;
	}

	void TrackballCamera::rotateUp(float degrees)
	{
		m_fAngleY += degrees;
	}

	glm::mat4 TrackballCamera::getViewMatrix() const
	{
		glm::mat4 viewMatrix;

		viewMatrix = glm::translate(glm::mat4(1), glm::vec3(0,0, -m_fDistance));

		viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(1,0,0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(0,1,0));

		return viewMatrix;
	}
}
