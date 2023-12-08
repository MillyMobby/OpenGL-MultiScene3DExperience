#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 color;

out vec2 uv;
out vec3 col;
void main() 
{
	uv = texCoord;
	col = color;
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
