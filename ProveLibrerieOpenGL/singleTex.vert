#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 color;
layout (location=3) in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv;
out vec3 col;
out vec3 norm;
//out vec3 fragPos;
out vec3 pos;

void main(){

	// openGL lavora per matrice a cui passi le righe

	uv= texCoord;
	col= color;
	norm = normal;
	//fragPos = position;
	pos = position;
	
	mat4 model = mat4(1.0);
	vec4 v1 = vec4(0.5, 0.0, 0.0, 0.5);
	vec4 v2 = vec4(0.0, 0.5, 0.0, 0.5);
	vec4 v3 = vec4(0.0, 0.0, 0.5, 0.5);
	vec4 v4 = vec4(0.0, 0.0, 0.0, 1.0);
	model = mat4(v1,v2,v3,v4);

	mat4 PVM = transpose(projectionMatrix) * transpose(viewMatrix) * transpose(modelMatrix);

	gl_Position = PVM * vec4(position, 1.0);
	//gl_Position = model * vec4(position, 1.0);

}
