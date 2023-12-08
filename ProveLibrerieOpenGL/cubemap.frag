#version 330 core
out vec4 FragColor;

uniform samplerCube cubeMap;	

in vec3 texCoords;

void main(){
	
	FragColor = texture(cubeMap, texCoords); //il terzo è il fattore di interpolazione: 0=prendi a, 1=prendi b
}