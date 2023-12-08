#version 330 core

out vec4 FragColor;

uniform vec3 cDiff;

struct Light{
	bool enable;
	vec3 WCL; // direzione luce nel world space che parte dalla luce (credo)
	vec3 cLight;
};

#define lightsMaxNumber 2 // da cambiare in base alle luci

uniform Light lights[lightsMaxNumber];

in vec3 WCN; // vettore direzione della normale del pixel
in vec3 WCV; // vettore di vista (! va dalla camera al pixel)
in vec2 uv;
in vec3 col;

void main(){

	vec3 WCNormal = normalize(WCN);
	vec3 radiance = vec3(0.0);
	for(int i=0; i<lightsMaxNumber; i++)
	{
		if(lights[i].enable)
		{
			vec3 WCLight = normalize(lights[i].WCL);
			float NdotL = max(dot(WCNormal, WCLight), 0.0);

			if(NdotL>0.0)
			{
				radiance += cDiff * NdotL * lights[i].cLight; 
			}
		}
	}
	FragColor = vec4(radiance, 1.0); // sarebbe l'eq. del rendering: BRDF = cLight (cDiff= colore materiale perché lambert), Li* cos(theta) = cLight(colore luce) * NdotL

}