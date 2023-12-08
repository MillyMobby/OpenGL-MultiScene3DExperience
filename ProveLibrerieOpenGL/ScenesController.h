#pragma once
#include "Scene.h"




class ScenesController
{
	typedef std::unordered_map<std::string, Scene> HashScene;
	typedef std::pair<std::string, Scene> HashScenePair;
private:
	HashScene _scenes;

public:
	void initScenes();

	Scene& getNextScene(const std::string& sceneName);

};