#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 uMVMatrix;				// Matrice ModelView
uniform mat4 uMVPMatrix;			// Matrice ModelViewProjection
uniform mat4 uNormalMatrix;		// Matrice Normale

out vec3 vPosition_vs;	// Positions dans l'espace View
out vec3 vNormal_vs;		// Normales dans l'espace View
out vec2 vTexCoords;		// Coords de texture au sommet

void main(){
	// Passage en coords homogènes
	vec4 vertexPosition = vec4(position, 1);
	vec4 vertexNormal   = vec4(normal, 0);

	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs   = vec3(uNormalMatrix * vertexNormal);
	vTexCoords   = texCoords;

	// Position projetée
  gl_Position = uMVPMatrix * vertexPosition;
}