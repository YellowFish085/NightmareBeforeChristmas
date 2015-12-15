#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

uniform sampler2D uTexture;                                                                 

uniform vec3 uKd;								//reflexion
uniform vec3 uKs;								//glossy
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

vec3 blinnPhong(){
	vec3 color;

	// Normalize vectors
	vec3 N = normalize(vNormal_vs);
	vec3 vectorToCam = normalize(-vPosition_vs);

	vec3 halfVector = (vectorToCam - uLightDir_vs)/2;
	color = uLightIntensity * (uKd * (dot(-uLightDir_vs,N)) + uKs * pow(dot(halfVector, N), uShininess));
	
	return color;
}

void main() {
	// Use blinnPhong instead of vec4 totalLight when lights are implemented
	vec4 totalLight = vec4(1.0, 1.0, 1.0, 1.0);

	fFragColor = vec3( texture2D(uTexture, vTexCoords.xy) * totalLight );
}