#include "projet/FreeflyCamera.hpp"

namespace Projet
{
  /* METHODES */
  /* Constructeurs */
  FreeflyCamera::FreeflyCamera() :
    m_Position(glm::vec3(0)),
    m_fPhi(M_PI),
    m_fTheta(0)
  {
    FreeflyCamera::computeDirectionVectors();
  };

  /* Déplacement */
  /* latéral */
  void FreeflyCamera::moveLeft(float distance)
  {
    m_Position += distance * m_LeftVector;
  };

  /* Frontal */
  void FreeflyCamera::moveFront(float distance)
  {
    m_Position += distance * m_FrontVector;
  };

  /* Rotation */
  /* y axis rotation */
  void FreeflyCamera::rotateLeft(float degrees)
  {
    m_fPhi += glm::radians(degrees);
    FreeflyCamera::computeDirectionVectors();
  };

  /* x axis rotation */
  void FreeflyCamera::rotateUp(float degrees)
  {
    m_fTheta += glm::radians(degrees);
    FreeflyCamera::computeDirectionVectors();
  };

  /* Divers */
  void FreeflyCamera::computeDirectionVectors()
  {
    m_FrontVector = glm::vec3(
      cos(m_fTheta)*sin(m_fPhi),
      sin(m_fTheta),
      cos(m_fTheta)*cos(m_fPhi)
    );

    m_LeftVector = glm::vec3(
      sin(m_fPhi + (M_PI/2)),
      0,
      cos(m_fPhi + (M_PI/2))
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
  };

  glm::mat4 FreeflyCamera::getViewMatrix() const
  {
    return glm::lookAt(m_Position, (m_FrontVector + m_Position), m_UpVector);
  };
}
