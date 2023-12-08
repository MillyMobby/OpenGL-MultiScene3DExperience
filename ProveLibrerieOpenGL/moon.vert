#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 color;
layout (location=3) in vec3 normal;
layout (location=4) in vec3 tangent;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv;
out vec3 norm;
out vec3 pos;
out mat3 TBN;

void main(){

	// openGL lavora per matrice a cui passi le righe

	uv= texCoord;
//	col= color;
	norm = normal;
	//fragPos = position;
	pos = position;

	vec3 bitangent = cross(normal,tangent);
	vec3 T = normalize(vec3(modelMatrix*vec4(tangent,0.0))); 
	vec3 B = normalize(vec3(modelMatrix*vec4(bitangent,0.0)));
	vec3 N = normalize(vec3(modelMatrix*vec4(normal * 0.5 + 0.5,0.0)));
	TBN = mat3(T,B,N);


	mat4 PVM = transpose(projectionMatrix) * transpose(viewMatrix) * transpose(modelMatrix);

	gl_Position = PVM * vec4(position, 1.0);
	//gl_Position = vec4(B, 1.0);
}