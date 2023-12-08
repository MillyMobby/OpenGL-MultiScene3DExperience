#version 330 core
out vec4 FragColor;

uniform sampler2D colorTex;
uniform sampler2D normalMap;

struct Light 
{
	bool enable;
	vec4 WCL; 
	vec3 cLight; 
};

#define lightsMaxNumber 3 

uniform Light lights[lightsMaxNumber];

in vec2 uv;
in vec3 pos; 
in mat3 TBN;


void main(){
	vec3 normal = texture(normalMap, uv).rgb;
	normal = normal * 2.0 - 1.0;  
	normal = normalize (TBN * normal);
	

	vec3 diffuse = vec3(0.0);
	for(int i=0; i< lightsMaxNumber; i++) {

		if(lights[i].enable){
			
			vec3 lightDir;
			if(lights[i].WCL.w == 0.0) { // se la luce è direzionale
			lightDir = normalize(-lights[i].WCL.xyz);
				diffuse += dot(normal, lights[i].WCL.xyz) * lights[i].cLight;
			}
			else if(lights[i].WCL.w == 1.0){ // se la luce ha una posizione
				vec3 lightDir = normalize(lights[i].WCL.xyz - pos);
				diffuse += max(dot(normal, lightDir),0.0) * lights[i].cLight;
			}
			
		}
		
	}

	vec3 T = TBN[0];
	vec3 B = TBN[1];
	vec3 N = TBN[2];

	
	FragColor = 2.3*vec4(diffuse,1.0) * texture(colorTex, uv); 
	//FragColor = texture(colorTex, uv);

}


