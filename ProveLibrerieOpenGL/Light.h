#pragma once
#include<string>
#include "Vec3f.h"
#include "Vec4f.h"


//NUOVA CLASSEE ---> FARE SOTTOCLASSI PER I VARI TIPI DI LUCE CHE CI SERVIRANNO
class Light
{
private:
	std::string _name = "";

	std::string _type; // tipo di luce

	Vec3f _position; // forse deve essere un vec4 in modo che posso controllare nel fragment (stessa cosa per _direction)
	Vec3f _lookAt; // solo per directional light 
	Vec3f _color = Vec3f(1.0, 1.0, 1.0);
	Vec3f _direction; //non c'è perché nella directional light direction = punto di rendering - _position oppure salvo la direzione nel vec3 della posizione
	bool _enable;

	float _kc; //fattore costante pointLight ---------------NEWWWWWWWWWWWWWWWWWWWWWWWW
	float _k1; // fattore lineare pointLight
	float _kq; //fattore quadratico pointLight

	float _theta = 0; // solo per spotLight

	float _ambientFactor = 0; // solo per luce ambientale

public:
	void setName(std::string name);

	void setType(std::string& t);
	std::string getType() const;

	void setPosition(Vec3f pos);
	void setColor(Vec3f color);
	void setLookAt(Vec3f lookAt);
	void setEnable(bool enable);
	void setDirection(Vec3f dir);

	void setKc(const float& k);
	float getKc() const;
	void setK1(const float& k);
	float getK1() const;
	void setKq(const float& k);
	float getKq() const;


	void setTheta(const float& angle);
	float getTheta() const;

	void setAmbientFactor(const float& f);
	float getAmbientFactor() const;

	std::string getName() const;
	Vec4f getPosition() const;
	Vec3f getColor() const;
	Vec3f getLookAt() const;
	Vec4f getDirection(); // MODIFICATAAA
	bool isEnable() const;

	Vec4f getWCL();

};