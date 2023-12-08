#version 330 core
out vec4 fragColor;
in vec3 uv;
in vec3 col;
uniform vec4 color;

void main() {
	fragColor = vec4(col, 1.0);
	//fragColor = vec4(1.0, 0.0,1.0, 1.0);

}