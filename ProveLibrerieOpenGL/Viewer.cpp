#include "Viewer.h"
#include "Configuration.h" // ----------------------- prova
#include "Vec4f.h"
#include "Viewer.h"
#include "Configuration.h" 

//Material mat;
//Mesh mesh;

void Viewer::setTitle(std::string t) {
	title = t;
}

const std::string& Viewer::getTitle() {
	return title;
}

void Viewer::setBackgroundColor(float r, float g, float b, float a) {
	backgroundColor.x = r;
	backgroundColor.y = g;
	backgroundColor.z = b;
	backgroundColor.w = a;
}

void Viewer::setBackgroundColor(Vec4f vecColor) {
	backgroundColor = vecColor;
}

void Viewer::setWidth(int w) {
	width = w;
}

void Viewer::setHeight(int h) {
	height = h;
}

void Viewer::setScene(Scene& scene) {
	_currentScene = scene;
}


bool Viewer::InitScene(Scene& scene) { // per ora non è usata
	return 1;
}

bool Viewer::Init(std::string sceneName) {

	_currentScene = scenesController.getNextScene(sceneName);
	_currentScene.init();

	return 1;
}


void Viewer::initFirstTime() {
	scenesController.initScenes();
	initWindow();
	_initializated = true;
}


bool Viewer::initWindow() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4); //anti aliasing
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	_windowSize.width = Configuration::getIstance().getWindowWidth();
	_windowSize.height = Configuration::getIstance().getWindowHeight();

	_windowSize.isChanged = false;

	_window = glfwCreateWindow(_windowSize.width, _windowSize.height, Configuration::getIstance().getWindowTitle().c_str(), NULL, NULL);

	glfwMakeContextCurrent(_window);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(_window, frameBufferSizeCB);
	glfwSetWindowUserPointer(_window, (void*)&_windowSize);
	return 1;
}
bool keyEnabled = true;
float timer = 0;

//NEW
void Viewer::processInput() {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}
	//const float cameraSpeed = static_cast <float>( 2.5 * deltaTime); // NON è USATAA
	std::string scene = _currentScene.getName();

	if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("FORWARD", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("BACKWARD", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("LEFT", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("RIGHT", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("ROTATION_SX", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("ROTATION_DX", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("ROTATION_UP", deltaTime, scene); }
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) { _currentScene.getCamera().ProcessKeyboard("ROTATION_DOWN", deltaTime, scene); }

	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		if (keyEnabled) {
			std::vector<std::string> triggerObjects = _currentScene.getTriggerObjects();
			for (int i = 0; i < triggerObjects.size(); ++i) {
				if (triggerObjects[i] == "") {
					_changeScene = true;
					_nextSceneName = _currentScene.getNextScene(triggerObjects[i]);
				}
				else {
					if (float d = _currentScene.distanceFromCamera(triggerObjects[i]) < 20.0) {
						_changeScene = true;
						_nextSceneName = _currentScene.getNextScene(triggerObjects[i]);
					}
				}
			}

			keyEnabled = false;
		}
	}

	_currentScene.updateCamera();

}

void Viewer::Run(std::string sceneName) { 

	if (_initializated) {

		if (Init(sceneName)) {

			while (!glfwWindowShouldClose(_window) && !_changeScene) { 

				glEnable(GL_DEPTH_TEST);
				glEnable(GL_MULTISAMPLE);

				float currentFrame = static_cast<float>(glfwGetTime());
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;

				if (!keyEnabled) {
					if (timer < 1) {
						timer += deltaTime;
					}
					else {
						timer = 0;
						keyEnabled = true;
					}
				}


				processInput();
				glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				if (_windowSize.isChanged) {
					_currentScene.getCamera().computeAspectRatio(_windowSize.width, _windowSize.height);
					_windowSize.isChanged = false;
				}


				_currentScene.updateCamera();


				_currentScene.launch(deltaTime);


				glfwSwapBuffers(_window);
				glfwPollEvents();
			}

			if (_changeScene) {

				if (_nextSceneName != _currentScene.getName()) {
					_currentScene.cleanScene();
					_changeScene = false;
					Run(_nextSceneName);
				}
				else {
					Clean();
				}
			}
			else {
				Clean();
			}
		}
	}
	else {
		std::cout << "ERROR:: WINDOW NOT INITIALIZATED";
	}
}

void Viewer::Clean() {

	glfwTerminate();
	_window = nullptr;

}


void Viewer::frameBufferSizeCB(GLFWwindow* window, int width, int height) {
	if (window != nullptr) {
		glViewport(0, 0, width, height);
		WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
		if (windowSize != nullptr) {
			windowSize->width = width;
			windowSize->height = height;
			windowSize->isChanged = true;
		}
	}
}