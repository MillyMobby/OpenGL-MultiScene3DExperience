#pragma once
#include <rapidxml.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "Material.h"
#include "Viewer.h"
#include "Vec4f.h"
#include "Object.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
class Configuration
{

	const std::string rootNodeStr = "info";

private:

	Configuration();
	Configuration(std::string fileName);
	~Configuration() = default;

	rapidxml::xml_document<> _configuration;
	std::vector<char> _buffer;
	rapidxml::xml_node<>* root_node = nullptr;


public:
	static Configuration& getIstance();

	int getWindowWidth();
	int getWindowHeight();
	std::string getWindowTitle();
	Viewer getView();
	Object getObject(rapidxml::xml_node<>* objectNode);
	bool getMesh(rapidxml::xml_node<>* node, Mesh& m);
	Camera getCamera();
	Camera getCamera(const std::string& sceneName);
	Light getLight(rapidxml::xml_node<>* lightNode);
	Texture getTexture(rapidxml::xml_node<>* materialNode);

	rapidxml::xml_node<>* getViewNode();
	rapidxml::xml_node<>* getMaterialsNode();
	rapidxml::xml_node<>* getMaterialsNode(rapidxml::xml_node<>* sceneNode);
	rapidxml::xml_node<>* getObjectsNode();
	rapidxml::xml_node<>* getObjectsNode(rapidxml::xml_node<>* sceneNode);
	rapidxml::xml_node<>* getLightsNode();
	rapidxml::xml_node<>* getLightsNode(rapidxml::xml_node<>* sceneNode);
	rapidxml::xml_node<>* getTextureNode();
	rapidxml::xml_node<>* getCameraNode();
	rapidxml::xml_node<>* getCameraNode(rapidxml::xml_node<>* sceneNode);
	rapidxml::xml_node<>* getScenesNode();
	rapidxml::xml_node<>* getSceneNode(std::string sceneName); //NUOVO PROVA SCENE

	Scene getScene(rapidxml::xml_node<>* sceneNode); // NUOVA CAMBIO SCENE

	rapidxml::xml_node<>* getMaterial(const std::string& materiale);
	rapidxml::xml_node<>* getMaterial(rapidxml::xml_node<>* sceneNode, const std::string& materiale);
	Material getMaterial(rapidxml::xml_node<>* materialNode);

	void applyUniforms(Material& mat);

	void applyUniforms(const std::string sceneName, Material& mat);




private:
	rapidxml::xml_node<>* getNode(rapidxml::xml_node<>* node, const std::string& tagName);
	rapidxml::xml_node<>* getNode(const std::string& tagName);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, std::string& str);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, int& value);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, bool& value);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, float& value);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, Vec3f& value);
	bool getValue(rapidxml::xml_node<>* node, Vec4f& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<float>& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<int>& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<std::string>& values);

};
