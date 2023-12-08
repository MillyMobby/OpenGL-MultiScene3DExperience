#version 330 core
out vec4 FragColor;

uniform sampler2D tex1;	//samapler2D uniform che si riferisce ad una texture


in vec2 uv;
in vec3 col;

void main(){
	FragColor= texture(tex1, uv); 
	//FragColor = vec4(col, 1.0);
	//FragColor= texture(tex3, uv); //il terzo è il fattore di interpolazione: 0=prendi a, 1=prendi b
}