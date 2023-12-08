#pragma once

#include "Material.h"
#include "Global.h"
#include "Object.h"

//#include "Material.h"
#include "Global.h"
#include "Object.h"

struct Trigger {
public:
	std::string objectName;
	std::string nextSceneName;
	Trigger(std::string obj, std::string scene) : objectName(obj), nextSceneName(scene) {};
};

class Scene
{

private:
	float timer = 0.0, tempoSprite = 0.2, spriteInd = 0.0;

	HashMaterial _materials;
	HashObject _objects;
	HashLight _lights;
	HashTexture _textures;

	std::string _name;
	std::vector<Trigger> _triggers;

	Material _cubeMap; //NEW PROVA PER ORA NON USATA
	Camera _camera;

	unsigned int _maxLightsNumber = 3;

public:
	Scene() {};
	Scene(const std::string& name) {
		_name = name;
	}
	~Scene() {
		cleanScene(); // MODIFICATO CAMBIO SCENE
	}

	Scene(const Scene& s) {
		_name = s._name;
		_materials = s._materials;
		_objects = s._objects;
		_lights = s._lights;
		_textures = s._textures;
		_triggers = s._triggers;
		_cubeMap = s._cubeMap; // forse non serve
		_camera = s._camera;
	}


	void setName(std::string name); // NEWWW
	std::string getName() const; // NEWWW


	void addTrigger(std::string obj, std::string nextScene); // NEWWW
	std::vector<std::string> getTriggerObjects(); // NEWWWW
	std::string getNextScene(std::string obj); // NEWWWW
	float distanceFromCamera(const std::string& objName); // 

	bool init();

	HashObject getObjects();
	bool initObject();
	void loadObjects();
	void loadMaterials();
	bool initMaterials();
	bool assignMaterialsToObjects();
	void loadLights(); // NEW LUCI LETI
	void loadCamera();

	void cleanScene();

	void launch(float deltaTime);


	Camera& getCamera();
	void updateCamera();

	bool initTexture();
	HashTexture getTextures();


	Material getMaterial() const;
};
