#include "Scene.h" 
#include "Configuration.h"

#include<cmath>



void Scene::loadMaterials() {
	rapidxml::xml_node<>* sceneNode = Configuration::getIstance().getSceneNode(_name);
	rapidxml::xml_node<>* materialsNode = Configuration::getIstance().getMaterialsNode(sceneNode);
	for (rapidxml::xml_node<>* materialNode = materialsNode->first_node("Material"); materialNode; materialNode = materialNode->next_sibling("Material"))
	{
		Material mat = Configuration::getIstance().getMaterial(materialNode);
		if (mat.getName() == "cubeMap") {
			_cubeMap = mat;
		}
		_materials.insert(HashMaterialPair(mat.getName(), mat));

		for (rapidxml::xml_node<>* samplerNode = materialNode->first_node("Sampler"); samplerNode; samplerNode = samplerNode->next_sibling("Sampler"))
		{
			Texture tex = Configuration::getIstance().getTexture(samplerNode);
			_textures.insert(HashTexturePair(tex.getTexName(), tex));
		}

	}
}



void Scene::loadObjects() {
	rapidxml::xml_node<>* sceneNode = Configuration::getIstance().getSceneNode(_name);
	rapidxml::xml_node<>* objectsNode = Configuration::getIstance().getObjectsNode(sceneNode);
	if (objectsNode != nullptr) {
		for (rapidxml::xml_node<>* objectNode = objectsNode->first_node("Object"); objectNode; objectNode = objectNode->next_sibling("Object"))
		{
			Object obj = Configuration::getIstance().getObject(objectNode);

			_objects.insert(HashObjectPair(obj.getName(), obj));

		}
	}
	else {
		std::cout << "ERRORE:: NON ESISTE IL NODO Objects nella scena " << _name;
	}
}


void Scene::loadCamera() {

	_camera = Configuration::getIstance().getCamera(_name);

	_camera.update();

}

void Scene::cleanScene() {
	for (auto& iteratorM : _materials) {
		iteratorM.second.clean();
	}
	_materials.clear();
	_objects.clear();
	_textures.clear();
	_lights.clear();
}

bool Scene::initMaterials() {
	bool ret = true;
	for (auto& iteratorM : _materials) {

		if (!iteratorM.second.buildMaterial()) {
			ret = false;
			break;
		}
		Configuration::getIstance().applyUniforms(_name, iteratorM.second);
	}
	return ret;
}

void Scene::setName(std::string name) {
	_name = name;
}

std::string Scene::getName() const {
	return _name;
}

void Scene::addTrigger(std::string obj, std::string nextScene) {
	_triggers.push_back(Trigger(obj, nextScene));
	std::cout << "";
}

std::vector<std::string> Scene::getTriggerObjects() {
	std::vector<std::string> triggers;
	for (int i = 0; i < _triggers.size(); ++i) {
		triggers.push_back(_triggers.at(i).objectName);
	}
	return triggers;
}

std::string Scene::getNextScene(std::string obj) {
	for (int i = 0; i < _triggers.size(); ++i) {
		if (_triggers.at(i).objectName == obj) {
			return _triggers.at(i).nextSceneName;
		}
	}
	return "";
}

float Scene::distanceFromCamera(const std::string& objName) {
	float distance = -1;
	Object obj = _objects.find(objName)->second;
	if (obj.isVisible()) {
		Vec4f objPos = _objects.find(objName)->second.getPosition();
		Vec4f cameraPos = Vec4f(_camera.getEye(), 1.0);
		distance = sqrt(pow(cameraPos.x - objPos.x, 2) + pow(cameraPos.y - objPos.y, 2) + pow(cameraPos.z - objPos.z, 2));
	}
	return distance;
}

bool Scene::init() {

	loadMaterials();
	initTexture();
	initMaterials();
	loadObjects();
	assignMaterialsToObjects();
	initObject();
	loadLights();
	loadCamera();
	return 1;
}

bool Scene::initObject() {

	bool rv = true;

	for (auto& it : _objects) {


		it.second.initGL();


	}

	return rv;
}

void Scene::launch(float deltaTime) {
	for (auto& itM : _materials) {
		if (itM.second.getName() == "cubeMap") { // disattivo il depth test per la cubeMap
			glDepthMask(GL_FALSE);
		}

		timer += deltaTime;
		itM.second.draw();

		if (timer > tempoSprite) {
			if (spriteInd >= 0.9) {
				spriteInd = 0;
			}
			else {
				spriteInd = spriteInd + 0.1;
			}
			timer = 0;
		}
		if (itM.second.getName() == "portaleTex") {
			itM.second.setF("SpriteTraslationX", spriteInd);

		}

		//--- TEXTURE
		for (auto itTU : itM.second.getTexturesUnit()) {
			auto itT = _textures.find(itTU.first);
			if (itT != _textures.end()) {
				glActiveTexture(GL_TEXTURE0 + itTU.second);
				itT->second.bind();
			}
		}

		// --- CAMERA
		itM.second.updateCameraUniform(_camera);

		float velocity = 5.5f * deltaTime;

		//---OBJECT
		for (auto& itOName : itM.second.getObjects()) {
			auto itO = _objects.find(itOName);
			if (itO != _objects.end()) {

				if (itO->second.rotates()) {
					Mat4f rot = Mat4f::rotateY(velocity / 4 * -3.141592653589793238463 / 8);
					Mat4f model = itO->second.getModelMatrix();
					itO->second.setModelMatrix(rot * model);
				}
				itM.second.updateObjectUniform(itO->second);
				itO->second.draw();
			}
		}

		glDepthMask(GL_TRUE);


		//---LUCI
		int lightIndex = 0;
		auto itL = _lights.begin();
		while (lightIndex < _maxLightsNumber) {
			Light light;
			bool isEnable = false;
			if (itL != _lights.end()) {
				light = itL->second;
				isEnable = light.isEnable();
				itL++;
			}
			else {
				lightIndex = 5;
			}
			if (isEnable) {
				itM.second.updateLightUniform(light, lightIndex, true);
				lightIndex++;
			}
		}
	}
}

HashObject Scene::getObjects() { return _objects; }


bool Scene::assignMaterialsToObjects() {

	bool rv = true;

	for (auto& it : _objects) {
		std::string matName = it.second.getMatName();
		std::string objName = it.second.getName();

		if (_materials.find(matName) != _materials.end()) {
			_materials.at(matName).addObject(objName, _objects);

		}
		else {
			rv = false;
			std::cout << "ERRORE::IL MATERIALE DELL'OGGETTO NON ESISTE" << std::endl;
			std::cout << matName << std::endl << std::endl;
			std::cout << objName << std::endl << std::endl;
		}
	}
	return rv;
}



void Scene::loadLights() {
	rapidxml::xml_node<>* lightsNode = Configuration::getIstance().getLightsNode(Configuration::getIstance().getSceneNode(_name));
	if (lightsNode != nullptr) {
		for (rapidxml::xml_node<>* lightNode = lightsNode->first_node("Light"); lightNode; lightNode = lightNode->next_sibling("Light"))
		{
			Light l = Configuration::getIstance().getLight(lightNode);
			_lights.insert(HashLightPair(l.getName(), l));
		}
	}

}


HashTexture Scene::getTextures() {
	return _textures;
}


bool Scene::initTexture() {

	bool rv = true;
	for (auto& itT : _textures) {
		if (!itT.second.initGL()) {
			rv = false;
			break;
		}
	}
	return rv;
}


Camera& Scene::getCamera() {
	return _camera;
}

void Scene::updateCamera() {
	_camera.update();
}