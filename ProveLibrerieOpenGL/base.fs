#version 330 core
out vec4 fragColor;
in vec3 uv;
in vec3 col;


uniform vec4 color;

void main() {
	fragColor=color;

}