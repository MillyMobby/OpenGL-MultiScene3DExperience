#include "ScenesController.h"

#include "Configuration.h"


void ScenesController::initScenes() {
	rapidxml::xml_node<>* scenesNode = Configuration::getIstance().getScenesNode();

	for (rapidxml::xml_node<>* sceneNode = scenesNode->first_node("Scene"); sceneNode; sceneNode = sceneNode->next_sibling("Scene"))
	{
		Scene s = Configuration::getIstance().getScene(sceneNode);
		_scenes.insert(HashScenePair(s.getName(), s));
		std::cout << "";
	}

}

Scene& ScenesController::getNextScene(const std::string& sceneName) {
	Scene scene;
	auto itS = _scenes.find(sceneName.c_str()); // controllo se non esiste la scena così non va bene
	if (itS != _scenes.end()) {
		return itS->second;
	}
	else {
		std::cout << "ERROR::LA SCENA SUCCESSIVA " << sceneName << "NON E' STATA TROVATA\n";
		return scene;
	}

}