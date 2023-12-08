#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 color;

out vec3 col;

void main()
{
	col = color;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}