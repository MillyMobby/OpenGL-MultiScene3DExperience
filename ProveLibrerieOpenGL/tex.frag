#version 330 core
out vec4 FragColor;

uniform sampler2D tex;	

struct Light 
{
	bool enable;
	vec4 WCL; // posizione o direzione
	vec3 cLight; // colore luce
	float kc;
	float k1;
	float kq;
};

#define lightsMaxNumber 3 

uniform Light lights[lightsMaxNumber];


in vec2 uv;
in vec3 pos;
in vec3 norm;

void main(){

	float attenuationFactor;
	
	vec3 diffuse = vec3(0.0);
	for(int i=0; i< lightsMaxNumber; i++) {

		if(lights[i].enable){
			
			vec3 lightDir;
			if(lights[i].WCL.w == 0.0) { // se la luce è direzionale
			lightDir = normalize(-lights[i].WCL.xyz);
				diffuse += dot(normalize(norm), lights[i].WCL.xyz) * lights[i].cLight;
				
			}
			else if(lights[i].WCL.w == 1.0){ // se la luce ha una posizione
				float d = length(vec3(pos) - vec3(lights[i].WCL.x,lights[i].WCL.y, lights[i].WCL.z));
				attenuationFactor = 1.0/ (lights[i].kc + lights[i].k1 * d + lights[i].kq * d*d);
				vec3 lightDir = normalize(lights[i].WCL.xyz - pos);

				diffuse += max(dot(normalize(norm), lightDir),0.0) * lights[i].cLight ;
			}
			
		}
		
	}
		
	FragColor = vec4((diffuse),1.0) * texture(tex, uv);

}