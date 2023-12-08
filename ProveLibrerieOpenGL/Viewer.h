/*
#include <string>
#include<glad.h>
#include <glfw3.h>*/
#pragma once
#include "Vec4f.h" 
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include "Mesh.h"
#include "ScenesController.h"
#include "Scene.h"



struct WindowSize {

public:
	WindowSize() { isChanged = false; width = 0; height = 0; }

	bool isChanged;
	int width;
	int height;
};

class Viewer
{

private:

	bool _initializated = false;
	ScenesController scenesController; //NEW CAMBIO SCENE

	bool _changeScene = false;
	std::string _nextSceneName;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f;


	std::string title = "";
	int width = 0;
	int height = 0;
	Vec4f backgroundColor = Vec4f();

	// finestra
	GLFWwindow* _window = nullptr;
	WindowSize _windowSize;

	Scene _currentScene; //CAMBIO NOME DA provaScena



public:
	Viewer() {};
	~Viewer() {
		delete _window;
	};

	void setTitle(std::string t);
	void setBackgroundColor(float r, float g, float b, float a);
	void setBackgroundColor(Vec4f vecColor);
	void setWidth(int w);
	void setHeight(int h);

	void setScene(Scene& scene);

	const std::string& getTitle();

	void Run(std::string sceneName);

	static void frameBufferSizeCB(GLFWwindow* window, int width, int height);

	void initFirstTime();


private:

	bool initWindow();

	void processInput();

	bool InitScene(Scene& scene);
	bool Init(std::string sceneName);
	void Clean();
};