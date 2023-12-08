#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 color;
layout (location=3) in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv;

out vec3 norm;
out vec3 pos;

void main() {

	uv= texCoord;

	norm = normal;
	pos = position;
	

	mat4 PVM = transpose(projectionMatrix) * transpose(viewMatrix) * transpose(modelMatrix);

	gl_Position = PVM * vec4(position, 1.0);
	

}

