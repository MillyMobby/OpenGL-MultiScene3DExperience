#version 330 core
out vec4 FragColor;

uniform sampler2D tex1;	//samapler2D uniform che si riferisce ad una texture
uniform sampler2D tex2;

in vec2 uv;
in vec3 col;

void main(){
	//FragColor= texture(tex1, uv); 
	//FragColor = vec4(col, 1.0);
	FragColor= mix(texture(tex1, uv), texture(tex2, uv), 0.5); //il terzo è il fattore di interpolazione: 0=prendi a, 1=prendi b
}