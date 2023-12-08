#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include <unordered_map>

class Material {

private:
	std::string _name = "";
	std::string _vShader = "";
	std::string _fShader = "";
	GLuint _shaderProgram = -1; //---------ho cambiato il nome

	std::string _uniformName;
	std::vector<float> _uniformVec;
	std::vector<std::string> _objects;

	//TEXTURE
	typedef std::unordered_map<std::string, int> HashTextureUnit;
	typedef std::pair<std::string, int> HashTextureUnitPair;
	HashTextureUnit _texturesUnit;

public:

	const static unsigned int maxLightsNumber = 3;

	Material() {};
	//Material(const Material& material){}; // senza parentesi {} da errore
	~Material() {
		_texturesUnit.clear();
	}

	void setName(std::string name);
	std::string& getName();
	void setVShader(std::string vShader);
	const std::string& getVShader();
	void setFShader(std::string fShader);
	const std::string& getFShader();
	GLuint getShaderProgram(); // PROBABILE CHE NON SERVIRà

	void setMat4(const std::string& name, const Mat4f& value); //NEW CAMERA
	void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w);
	void setVec3(const std::string name, const float& x, const float& y, const float& z); // NEW LUCI 
	void setI1(const std::string name, const bool& b); //NEW LUCI 
	void setT1(const std::string name, const int& b); // NEW ARI
	void setVec4i(const std::string& name, const int& x, const int& y, const int& z, const int& w); //NEW ARI
	void setF(const std::string name, const float& f); //NEW ARI

	void setUniform(const std::string& name, std::vector<int> value, const int& count = -1);//NEW ARIIIIIIIII ??????
	void setUniform(const std::string& name, std::vector<float> value, const int& count);
	void updateLightUniform(Light& light, const int& lightIndex, const bool& isEnable);//NEW LUCI
	void updateCameraUniform(const Camera& cam);//NEW CAMERA
	void updateObjectUniform(Object obj);

	bool buildMaterial(const std::string& vShaderPath, const std::string& fShaderPath);
	bool compile(const std::string& shaderCode, const GLenum& shaderType, GLuint& shader);
	bool link(const GLuint& vShader, const GLuint& fShader);

	void clean();
	bool readShader(const std::string& path, std::string& shader);
	bool buildMaterial();

	void draw();


	void addObject(std::string name, std::unordered_map<std::string, Object> objList);
	const std::vector<std::string>& getObjects() const;
	void removeObject(std::string name, std::unordered_map<std::string, Object> objList);


	void updateLightUniform(const Light& light, const int& lightIndex, const bool& isEnabled);//NEW LETI LUCI



	//NEW per texture
	void addTexture(std::string textureName, int textureUnit);
	const HashTextureUnit& getTexturesUnit() const;
};


//Scene{
//	init();
//}

//
//class Texture {
//
//};



//la scena ha un dizionario di texture
//il materiale si riferisce alle texture (?!della scena)
//nel Viewer chiedo al materiale quali texture prendere e bindo


//NON ABBIAMO BISOGNO DI CAMBIARE LO UNIFORM DURANTE IL RENDERING REAL TIME

//SE VOGLIO CAMBIARE COLORE DURANTE IL FLUSSO??? MODIFICO LO UNIFORM

//CAMBIARE LA TEXTURE INVECE è PIù COMPLICATO


//glfwGetTime(); --> USARE QUESTA FUNZIONE (quanto tempo è passato dall'inizio del programma)

//!!!!NON FARE MAI ERRORE DI CALCOLARE TEMPO FRA UN FRAME E UN ALTRO!!! --> USARE IL WALL CLOCK CHE è UN OROLOGIO FISSO 