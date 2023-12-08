#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 color;
layout (location=3) in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 texCoords;


void main(){

	
	texCoords = position;

	gl_Position = transpose(projectionMatrix) * transpose(viewMatrix) *  vec4(position , 1.0);

}