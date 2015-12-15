#include <glimac/glm.hpp>
#include <cmath>

namespace Projet
{
  class FreeflyCamera
  {
    /* ATTRIBUTS */
    private :
      glm::vec3 m_Position;
      float m_fPhi;
      float m_fTheta;
      glm::vec3 m_FrontVector;
      glm::vec3 m_LeftVector;
      glm::vec3 m_UpVector;

    /* METHODES */
    public :
      /* Constructeurs */
      FreeflyCamera();

      /* Déplacement */
      /* latéral */
      void moveLeft(float distance);

      /* frontal */
      void moveFront(float distance);

      /* Rotation */
      /* y axis rotation */
      void rotateLeft(float degrees);

      /* x axis rotation */
      void rotateUp(float degrees);

    /* Divers */
    private :
      void computeDirectionVectors();

    public :
      glm::mat4 getViewMatrix() const;
  };
};
