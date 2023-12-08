#version 330 core
out vec4 FragColor;


uniform vec4 cDiff; // colore materiale

struct Light 
{
	bool enable;
	vec3 WCN;
	vec3 cLight; // colore luce
};

vec3 lightPos = vec3(1.0, 0.0, 0.0); // momentaneo

#define lightsMaxNumber 2 // da cambiare in base alle luci

uniform Light lights[lightsMaxNumber];

in vec3 WCN;
in vec3 WCV;
in vec3 uv;
in vec3 col;
in vec3 normal;

in vec3 fragPos; // posizione del pixel

void main() 
{

	
	vec3 ambient = vec3(1.0, 1.0, 1.0) * 0.2;
	//vec3 lightDir = normalize(lightPos - fragPos);
	vec3 lightDir = vec3(0.0, 1.0, 0.0); // la definisco manualmente
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * lights[0].cLight;

	vec4 colorObject = vec4(1.0);
	FragColor = vec4(diffuse + ambient, 1.0) * cDiff ;

}