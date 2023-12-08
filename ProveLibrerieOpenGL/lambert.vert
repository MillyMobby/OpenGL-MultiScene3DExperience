#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 color;
layout (location = 3) in vec3 normal;

out vec3 WCN; 
out vec3 WCV;
//out vec3 fragPos;
out vec2 uv;
out vec3 col;
//out vec3 nor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 normalMatrix;
uniform mat4 viewMatrixInverse;


void main()
{
	WCN = normalize((normalMatrix * vec4(normal, 0.0)).xyz); // vettore normale al vertice moltiplicato per la normalMatrix che è l'equivalente della modelMatrix ma per le normali
	vec4 vertex = vec4(position, 1.0); // posizione del vertice nel local space + coordinata finale
	vec4 VCPos = viewMatrix * modelMatrix * vertex; // posizione del vertice nel viewSpace(camera) 
	WCV = normalize((viewMatrixInverse * vec4(VCPos.xyz, 0.0)).xyz); // moltiplico per l'inversa il vettore che va dall'eye della camera al vertice per ottenere il vettore di vista nel world space

	uv = texCoord;
	col = color;

	gl_Position = projectionMatrix * VCPos; // posizione vertice nel clip space
}