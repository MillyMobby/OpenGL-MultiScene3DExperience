#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 color;
layout (location = 3) in vec3 aNormal;

out vec3 fragPos;
out vec3 col;
out vec3 normal;

void main()
{
	col = color;
	fragPos = aPos; // passo la osizione del vertice per trovare la posizione del pixel
	normal = aNormal;// per ora la metto io manualmente
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}