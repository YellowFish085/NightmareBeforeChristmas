#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

struct Light {
	int type;
	vec3 intensity;
	vec3 position;
};

uniform sampler2D uTexture;

uniform vec3 uKd;								//reflexion
uniform vec3 uKs;								//glossy
uniform float uShininess;
uniform Light uLights[10];
uniform int uNbLights;

out vec3 fFragColor;

vec3 blinnPhong(Light light){

	vec3 uLightIntensity = light.intensity;


	if(light.type == 1) // Directional Light
	{
		vec3 color;
		vec3 uLightDir_vs = -(light.position);

		vec3 N = normalize(vNormal_vs);
		vec3 vectorToCam = normalize(-vPosition_vs);
		vec3 halfVector = (vectorToCam - uLightDir_vs)/2;

		vec3 Kd = texture(uTexture, vTexCoords).rgb;

		color = uLightIntensity*(Kd*max(dot(uLightDir_vs, N), 0.0) + uKs * pow(max(dot(halfVector, N), 0.0), uShininess));

		return color;
	}
	else if(light.type == 2) // Point Light
	{
		vec3 color;

		vec3 uLightPos_vs = light.position;

		float distanceToFrag = distance(uLightPos_vs, vPosition_vs);
		vec3 LightIntensity = uLightIntensity / (distanceToFrag * distanceToFrag);

		vec3 N = normalize(vNormal_vs);

		vec3 lightSrcPos = normalize(vPosition_vs - uLightPos_vs);
		vec3 vectorToCam = normalize(-vPosition_vs);
		vec3 halfVector = (vectorToCam - lightSrcPos)/2;

		vec3 Kd = texture(uTexture, vTexCoords).rgb;

		color = LightIntensity*(Kd*(max(dot(-lightSrcPos,N), 0.0)) + uKs * pow(max(dot(halfVector, N), 0.0), uShininess));
		return color;
	}
	else // Ambient Light
	{
		vec3 color;
		//OUT.Specular = intensity * light.specularColor * light.specularPower / distance;
		vec3 Kd = texture(uTexture, vTexCoords).rgb;
		vec3 N = normalize(vNormal_vs);
		vec3 vectorToCam = normalize(vPosition_vs);
		vec3 halfVector = (-vectorToCam)/2;

		color = max(light.intensity * Kd,0.0);
		return color;
	}
}

void main() {
	fFragColor = blinnPhong(uLights[0]);
	for(int i = 1;  i < uNbLights; i++)
	{
		fFragColor += blinnPhong(uLights[i]);
	}
}
