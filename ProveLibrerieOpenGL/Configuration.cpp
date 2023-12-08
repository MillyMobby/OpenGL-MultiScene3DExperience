#include "Configuration.h"
#include <fstream>
#include <sstream>
#include "Configuration.h"
#include <fstream>
#include <sstream>


Configuration::Configuration() {

	ifstream file("config.xml"); // passo il nome del file ???????

	_buffer = vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	_buffer.push_back('\0');
	_configuration.parse<0>(&_buffer[0]);

	root_node = _configuration.first_node("info");
}

Configuration& Configuration::getIstance() {
	static Configuration istance;
	return istance;
}

rapidxml::xml_node<>* Configuration::getNode(rapidxml::xml_node<>* node, const std::string& tagName) {
	rapidxml::xml_node<>* result_node = nullptr;
	if (node != nullptr) {
		if (node->first_node(tagName.c_str())) {
			result_node = node->first_node(tagName.c_str());
		}
	}
	else { std::cout << "non esiste il nodo " << tagName << std::endl; }
	return result_node;
}

rapidxml::xml_node<>* Configuration::getNode(const std::string& tagName) {

	return getNode(root_node, tagName);
}


bool Configuration::getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, std::string& str) {
	bool exist = false;
	if (node->first_attribute(tagName.c_str())) {
		str = node->first_attribute(tagName.c_str())->value();
		exist = true;
	}
	return exist;
}

bool Configuration::getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, int& value) {
	bool exist = false;
	if (node != nullptr) {
		if (node->first_attribute(tagName.c_str())) {
			value = stoi(node->first_attribute(tagName.c_str())->value());
			exist = true;
		}
	}
	else {
		std::cout << "non esiste l' attributo " << tagName;
	}
	return exist;
}

bool Configuration::getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, bool& value) {
	bool exist = false;
	if (node != nullptr) {
		if (node->first_attribute(tagName.c_str())) {
			value = stoi(node->first_attribute(tagName.c_str())->value());
			exist = true;
		}
	}
	else {
		std::cout << "non esiste l' attributo " << tagName;
	}
	return exist;
}

bool Configuration::getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, float& value) {
	bool exist = false;
	if (node != nullptr) {
		if (node->first_attribute(tagName.c_str())) {
			value = stof(node->first_attribute(tagName.c_str())->value());
			exist = true;
		}
	}
	else {
		std::cout << "non esiste l' attributo " << tagName;
	}
	return exist;
}


// NEW LETI PER PRENDERE VEC3F (richiamato da getLight)
bool Configuration::getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, Vec3f& vec) {

	bool exist = false;
	std::string str;
	if (node != nullptr) {
		if (node->first_attribute(tagName.c_str())) {
			str = node->first_attribute(tagName.c_str())->value();
			std::stringstream ss(str);
			float v;
			int i = 0;
			std::vector<float> tempVector;
			while (ss >> v) {
				if (ss.peek() == ',') {
					ss.ignore();
				}
				tempVector.push_back(v);
			}
			if (tempVector.size() == 3) {
				vec.x = tempVector.at(0);
				vec.y = tempVector.at(1);
				vec.z = tempVector.at(2);
				exist = true;
			}
			else {
				std::cout << "ERRORE: i valori inseriti nel tag " << tagName << " non sono corretti, ne vanno inseriti 3 " << std::endl;
			}
		}
		else {
			std::cout << "non esiste l' attributo " << tagName;
		}
	}
	else {
		std::cout << "ERRORE: nodo null ";
	}

	return exist;
}


//MODIFICATO LETI PER NON RIPETERE CODICE
bool Configuration::getValue(rapidxml::xml_node<>* node, Vec4f& values) {
	bool exist = false;


	std::vector<float> tempValues;
	if (getValue(node, tempValues)) {
		if (tempValues.size() != 4) {
			std::cout << "ERRORE: i valori devono essere 4 ma non lo sono";
		}
		else {
			values = Vec4f(tempValues[0], tempValues[1], tempValues[2], tempValues[3]);
			exist = true;
		}
	}
	return exist;
}


bool Configuration::getValue(rapidxml::xml_node<>* node, std::vector<float>& values) {
	bool exist = false;

	if (node != nullptr) {
		std::string stringData = node->value();
		std::stringstream ss(stringData);
		float v;


		while (ss >> v) {
			if (ss.peek() == ',') {
				ss.ignore();
			}
			values.push_back(v);
		}

		exist = true;

	}

	return exist;
}


bool Configuration::getValue(rapidxml::xml_node<>* node, std::vector<int>& values) {
	bool exist = false;

	if (node != nullptr) {
		std::string stringData = node->value();
		std::stringstream ss(stringData);
		int v;

		while (ss >> v) {
			if (ss.peek() == ',') {
				ss.ignore();
			}
			values.push_back(v);
		}
		exist = true;
	}
	return exist;

}



bool Configuration::getValue(rapidxml::xml_node<>* node, std::vector<std::string>& values) {
	bool exist = false;

	if (node != nullptr) {
		std::string stringData = node->value();
		std::stringstream ss(stringData);
		std::string v;
		if (stringData != "") {
			while (ss >> v) {
				if (ss.peek() == '\n') {
					ss.ignore();
				}
				values.push_back(v);
			}
			exist = true;
		}

	}

	return exist;

}





rapidxml::xml_node<>* Configuration::getViewNode() {
	return getNode("View");
}


rapidxml::xml_node<>* Configuration::getMaterialsNode() {
	return getNode("Materials");
}

rapidxml::xml_node<>* Configuration::getMaterialsNode(rapidxml::xml_node<>* sceneNode) {
	return getNode(sceneNode, "Materials");
}

rapidxml::xml_node<>* Configuration::getObjectsNode() {
	return getNode("Objects");
}

rapidxml::xml_node<>* Configuration::getObjectsNode(rapidxml::xml_node<>* sceneNode) {
	return getNode(sceneNode, "Objects");
}



rapidxml::xml_node<>* Configuration::getLightsNode() {
	return getNode("Lights");
}

rapidxml::xml_node<>* Configuration::getLightsNode(rapidxml::xml_node<>* sceneNode) {
	return getNode(sceneNode, "Lights");
}

rapidxml::xml_node<>* Configuration::getCameraNode() { // non è usata
	return getNode("Camera");
}

rapidxml::xml_node<>* Configuration::getCameraNode(rapidxml::xml_node<>* sceneNode) { //new
	return getNode(sceneNode, "Camera");
}
rapidxml::xml_node<>* Configuration::getScenesNode() { // NUOVO
	return getNode("Scenes");
}

rapidxml::xml_node<>* Configuration::getSceneNode(std::string sceneName) { //MODIFICATO SCENEEEE
	rapidxml::xml_node<>* scenesNode = getNode("Scenes");
	rapidxml::xml_node<>* sceneNode;
	std::string strAttr;

	for (sceneNode = getNode(scenesNode, "Scene"); sceneNode; sceneNode = sceneNode->next_sibling("Scene")) {
		getAttribute(sceneNode, "name", strAttr);
		if (strAttr == sceneName.c_str()) { //PROBLEMA CHE L'UGUALE NON FUNZIONA BENE E COMUNQUE SE LA SCENA NON ESISTE CONTINUA A CERcarla in loop

			return sceneNode;
		}
	}
	std::cout << "ERRORE::Non è stata trovata nessuna scena nell'xml con il nome " << sceneName;


	return sceneNode;
}

Scene Configuration::getScene(rapidxml::xml_node<>* sceneNode) {

	Scene s;

	std::string attrString;

	if (getAttribute(sceneNode, "name", attrString)) { s.setName(attrString); }


	if (rapidxml::xml_node<>* triggersNode = getNode(sceneNode, "Triggers")) {
		if (triggersNode != nullptr) {// se è nullptr non esiste il trigger


			std::string objectName;
			std::string nextSceneName;
			for (auto triggerNode = getNode(triggersNode, "Trigger"); triggerNode; triggerNode = triggerNode->next_sibling("Trigger")) {
				if (getAttribute(triggerNode, "object", objectName) && getAttribute(triggerNode, "nextScene", nextSceneName)) {
					s.addTrigger(objectName, nextSceneName);
				}
				else {
					std::cout << "ERROR::non sono stati specificati oggetto e scena successiva trigger della scena " << s.getName() << std::endl;
				}
			}
		}
	}


	return s;
}


int Configuration::getWindowWidth() {

	rapidxml::xml_node<>* windowNode = getNode(getViewNode(), "Window");


	int attrInt = 0;

	if (getAttribute(windowNode, "width", attrInt)) { return attrInt; }
	return attrInt;
}

int Configuration::getWindowHeight() {

	rapidxml::xml_node<>* windowNode = getNode(getViewNode(), "Window");


	int attrInt = 0;

	if (getAttribute(windowNode, "height", attrInt)) { return attrInt; }
	return attrInt;
}

std::string Configuration::getWindowTitle() {

	rapidxml::xml_node<>* windowNode = getNode(getViewNode(), "Window");

	std::string attr = "";

	if (getAttribute(windowNode, "title", attr)) { return attr; }
	return attr;
}


Viewer Configuration::getView() {

	rapidxml::xml_node<>* viewerNode = getViewNode();

	rapidxml::xml_node<>* windowNode = getNode(viewerNode, "Window");

	Viewer v;
	std::string attrString;

	int attrInt = 0;

	Vec4f backgroundColor;

	if (getAttribute(windowNode, "title", attrString)) { v.setTitle(attrString); }
	if (getAttribute(windowNode, "width", attrInt)) { v.setWidth(attrInt); }
	if (getAttribute(windowNode, "height", attrInt)) { v.setHeight(attrInt); }


	if (getValue(getNode(viewerNode, "Background"), backgroundColor)) {
		v.setBackgroundColor(backgroundColor);
	}

	return v;
}

rapidxml::xml_node<>* Configuration::getMaterial(const std::string& materiale) { // torna il nodo del material giusto

	std::string attrString = "";
	rapidxml::xml_node<>* materialsNode = getMaterialsNode();


	for (rapidxml::xml_node<>* materialNode = materialsNode->first_node("Material"); materialNode; materialNode = materialNode->next_sibling("Material"))
	{
		getAttribute(materialNode, "name", attrString);

		if (attrString == materiale) {

			return materialNode;
		}

	}

	return nullptr;
}

rapidxml::xml_node<>* Configuration::getMaterial(rapidxml::xml_node<>* sceneNode, const std::string& materiale) { // torna il nodo del material giusto

	std::string attrString = "";
	rapidxml::xml_node<>* materialsNode = getMaterialsNode(sceneNode);


	for (rapidxml::xml_node<>* materialNode = materialsNode->first_node("Material"); materialNode; materialNode = materialNode->next_sibling("Material"))
	{
		getAttribute(materialNode, "name", attrString);

		if (attrString == materiale) {

			return materialNode;
		}

	}

	return nullptr;
}




Material Configuration::getMaterial(rapidxml::xml_node<>* materialNode) {
	Material m;
	string attrString;

	rapidxml::xml_node<>* materialsNode = getNode("Materials");

	if (getAttribute(materialNode, "name", attrString)) { m.setName(attrString); }
	if (getAttribute(materialNode, "vs", attrString)) { m.setVShader(attrString); }
	if (getAttribute(materialNode, "fs", attrString)) { m.setFShader(attrString); }

	return m;
}


Object Configuration::getObject(rapidxml::xml_node<>* objectNode) {
	Object obj;
	std::string attrString;
	bool boolAttr;

	if (objectNode) {

		if (getAttribute(objectNode, "path", attrString)) { obj.setPath(attrString); }

		if (obj.getPath().length() > 0) {
			obj = Object::loadFromFile(obj.getPath());
		}
		else {
			if (!getMesh(objectNode, obj.getMesh())) { // riempe direttamente la Mesh che gli viene passata
				std::cout << "ERRORE::la Mesh non è stata letta dal file xml per quanto riguarda l'oggetto " << obj.getName() << std::endl;
			}
		}
		if (getAttribute(objectNode, "name", attrString)) { obj.setName(attrString); }
		if (getAttribute(objectNode, "material", attrString)) { obj.setMatName(attrString); }
		if (getAttribute(objectNode, "visible", boolAttr)) { obj.setVisible(boolAttr); }

		if (getAttribute(objectNode, "rotates", boolAttr)) { obj.setRot(boolAttr); } 
 

        for (rapidxml::xml_node<>* trasformationNode = objectNode->first_node("Trasformation"); trasformationNode; trasformationNode = trasformationNode->next_sibling("Trasformation"))
        {
 
            Mat4f model = Mat4f(1.0f);
            std::vector<float> fat;
 
            if (rapidxml::xml_node<>* scaleNode = getNode(trasformationNode, "Scale")) {
 
                getValue(scaleNode, fat);
                model = model.scaleMatrix(fat.at(0), fat.at(1), fat.at(2));
                std::cout << "scale: " << model << std::endl;
                fat.clear();
            }
 

            if (rapidxml::xml_node<>* translateNode = getNode(trasformationNode, "Translate")) {
 
                getValue(translateNode, fat);
                model = model.translation(fat.at(0), fat.at(1), fat.at(2)) * model;
                std::cout << "translate: " << model << std::endl;
                fat.clear();
 
            }
            if (rapidxml::xml_node<>* rotationXNode = getNode(trasformationNode, "RotateX")) {
 
                getValue(rotationXNode, fat);
                model = model.rotateX(3.141592653589793238463 / fat.at(0)) * model;
                std::cout << "rotateX: " << model << std::endl;
                fat.clear();
 
            }
			if(rapidxml::xml_node<>*rotationYNode = getNode(trasformationNode, "RotateY")) {

				getValue(rotationYNode, fat);
				std::cout << "rotateY " << fat.at(0);
				Mat4f rotY = Mat4f::rotateY(3.141592653589793238463);
				model = rotY * model;
				std::cout << "rotateY: " << model << std::endl;
				fat.clear();

			}
 
            obj.setModelMatrix(model);
 
        }
 
    }
 
    return obj;
}

bool Configuration::getMesh(rapidxml::xml_node<>* node, Mesh& m) {
	bool control = false;
	rapidxml::xml_node<>* meshNode;
	bool boolAttr;
	int intAttr;
	std::vector<float> vertices;

	if (meshNode = getNode(node, "Mesh")) {

		if (getAttribute(meshNode, "numVertices", intAttr)) {} 

		if (getAttribute(meshNode, "hasPosition", boolAttr)) { m.setHasPositions(boolAttr); } // m.setHasPositions(boolAttr);
		if (getAttribute(meshNode, "hasTextureCoords0", boolAttr)) { m.setHasTexCoords(boolAttr); }
		if (getAttribute(meshNode, "hasVertexColors", boolAttr)) { m.setHasVertexColor(boolAttr); }
		if (getAttribute(meshNode, "hasNormals", boolAttr)) { m.setHasNormals(boolAttr); }
		if (getAttribute(meshNode, "hasTangents", boolAttr)) { m.setHasTangents(boolAttr); }

		if (getValue(getNode(meshNode, "Vertices"), vertices)) {
			m.setVertices(vertices);
		}


		if (rapidxml::xml_node<>* faceNode = getNode(meshNode, "Faces")) {
			
			std::vector<int> tempIndices;
			getValue(faceNode, tempIndices);
			for (int i = 0; i < tempIndices.size(); i = i++) {
				m.addToIndices(tempIndices.at(i));
			}
		}
		else {
			std::cout << "NON SONO PRESENTI FACCE" << std::endl;
		}


		control = true;
	}
	else { std::cout << "Non esiste questa Mesh"; }

	return control;

}

Light Configuration::getLight(rapidxml::xml_node<>* lightNode) {
	Light light;

	std::string attrString;
	Vec3f vec3Attr;
	bool boolAttr;
	float floatAttr;

	if (lightNode) {
		if (getAttribute(lightNode, "name", attrString)) { light.setName(attrString); }

		if (getAttribute(lightNode, "position", vec3Attr)) { light.setPosition(vec3Attr); }
		if (getAttribute(lightNode, "color", vec3Attr)) { light.setColor(vec3Attr); }
		if (getAttribute(lightNode, "lookAt", vec3Attr)) { light.setLookAt(vec3Attr); }
		if (getAttribute(lightNode, "enable", boolAttr)) { light.setEnable(boolAttr); }
		if (getAttribute(lightNode, "direction", vec3Attr)) { light.setDirection(vec3Attr); }

		if (getAttribute(lightNode, "theta", floatAttr)) {
			light.setTheta(floatAttr);


		} // se è presente ho un faretto

	}

	return light;
}

void Configuration::applyUniforms(const std::string sceneName, Material& mat) {
	rapidxml::xml_node<>* sceneNode = getSceneNode(sceneName);
	rapidxml::xml_node<>* materialNode = getMaterial(sceneNode, mat.getName());

	if (materialNode != nullptr) {
		rapidxml::xml_node<>* uniformNode = materialNode->first_node();
		std::cout << "a";
		for (rapidxml::xml_node<>* uniformNode = materialNode->first_node(); uniformNode; uniformNode = uniformNode->next_sibling())
		{
			std::string nodeName = uniformNode->name();
			if (nodeName.compare("Uniform") == 0) {

				std::string name = "";
				char type = '0';
				int count = 0;

				std::string s;
				s.push_back(type);
				if (getAttribute(uniformNode, "name", name) &&
					getAttribute(uniformNode, "type", s) &&
					getAttribute(uniformNode, "count", count))
					
				{
					switch (s.at(0)) {
					case 'f': {
						std::vector<float> _values;
						if (getValue(uniformNode, _values)) {
							mat.setUniform(name, _values, count);

						}
						break;
					}
					case 'i': { 
						std::vector<int> _values;
						if (getValue(uniformNode, _values)) {
							mat.setUniform(name, _values, count);
						}
						break;
					}

					default:
						std::cout << "break apply" << std::endl;
						break;
					}
				}
			}
			else if (nodeName.compare("Sampler") == 0) {
				std::string name = "";
				std::string textureName = "";
				if (getAttribute(uniformNode, "name", name) && getAttribute(uniformNode, "textureName", textureName)) {
					std::vector<int> _values;
					int value;
					if (getAttribute(uniformNode, "texUnit", value)) { 
						_values.push_back(value);
						mat.setUniform(name, _values, 1);
						mat.addTexture(textureName, _values[0]);
					}
				}
			}

		}
	}
}


void Configuration::applyUniforms(Material& mat) {

	rapidxml::xml_node<>* materialNode = getMaterial(mat.getName());
	std::cout << "nome materiale dello uniform " << mat.getName() << std::endl;

	if (materialNode != nullptr) {
		rapidxml::xml_node<>* uniformNode = materialNode->first_node();
		std::cout << "a";
		for (rapidxml::xml_node<>* uniformNode = materialNode->first_node(); uniformNode; uniformNode = uniformNode->next_sibling())
		{
			//NEW TEXTURE:
			std::string nodeName = uniformNode->name();
			if (nodeName.compare("Uniform") == 0) {

				std::string name = "";
				char type = '0';
				int count = 0;

				std::string s;
				s.push_back(type);
				if (getAttribute(uniformNode, "name", name) &&
					getAttribute(uniformNode, "type", s) &&
					getAttribute(uniformNode, "count", count))
					
				{
					switch (s.at(0)) {
					case 'f': {
						std::vector<float> _values;
						if (getValue(uniformNode, _values)) {
							mat.setUniform(name, _values, count);

						}
						break;
					}
					case 'i': { 
						std::vector<int> _values;
						if (getValue(uniformNode, _values)) {
							mat.setUniform(name, _values, count);
						}
						break;
					}

					default:
						std::cout << "break apply" << std::endl;
						break;
					}
				}
			}
			else if (nodeName.compare("Sampler") == 0) {
				std::string name = "";
				std::string textureName = "";
				if (getAttribute(uniformNode, "name", name) && getAttribute(uniformNode, "textureName", textureName)) {
					std::vector<int> _values;
					int value;
					if (getAttribute(uniformNode, "texUnit", value)) { 
						_values.push_back(value);
						mat.setUniform(name, _values, 1);
						mat.addTexture(textureName, _values[0]);
					}
				}
			}

		}
	}
}





Texture Configuration::getTexture(rapidxml::xml_node<>* textureNode) {

	Texture t;
	string attrString = "";
	std::vector<std::string> attrStingvec;

	if (getAttribute(textureNode, "name", attrString)) { t.setName(attrString); }
	if (getAttribute(textureNode, "type", attrString)) { t.setType(attrString); }
	if (getAttribute(textureNode, "textureName", attrString)) { t.setTexName(attrString); }
	//if (getAttribute(textureNode, "imagePath", attrString)) { t.setImagePath(attrString); } 
	if (getAttribute(textureNode, "minFilter", attrString)) { t.setMinFilter(attrString); }
	if (getAttribute(textureNode, "magFilter", attrString)) { t.setMagFilter(attrString); }
	if (getAttribute(textureNode, "wrapS", attrString)) { t.setWrapS(attrString); }
	if (getAttribute(textureNode, "wrapT", attrString)) { t.setWrapT(attrString); }
	if (getAttribute(textureNode, "wrapR", attrString)) { t.setWrapR(attrString); }


	if (getValue(textureNode, attrStingvec)) { t.setImagesPats(attrStingvec); }

	return t;

}



Camera Configuration::getCamera() {
	Camera rv;
	rapidxml::xml_node<>* cameraNode = getNode("Camera");
	if (cameraNode != nullptr) {

		float attr = 0.0f;
		std::vector<float> _values;
		if (getAttribute(cameraNode, "fovH", attr)) { rv.setFov(attr); }
		if (getAttribute(cameraNode, "near", attr)) { rv.setNear(attr); }
		if (getAttribute(cameraNode, "far", attr)) { rv.setFar(attr); }

		if (getValue(cameraNode, _values)) {

			rv.setEye(Vec3f(_values[0], _values[1], _values[2]));
			rv.setLookAt(Vec3f(_values[3], _values[4], _values[5]));
			rv.setup(Vec3f(_values[6], _values[7], _values[8]));
		}
		rv.computeAspectRatio(getWindowWidth(), getWindowHeight());
	}
	return rv;
}



Camera Configuration::getCamera(const std::string& sceneName) {
	Camera rv;
	rapidxml::xml_node<>* cameraNode = getNode(getSceneNode(sceneName), "Camera");
	if (cameraNode != nullptr) {

		float attr = 0.0f;
		std::vector<float> _values;
		if (getAttribute(cameraNode, "fovH", attr)) { rv.setFov(attr); }
		if (getAttribute(cameraNode, "near", attr)) { rv.setNear(attr); }
		if (getAttribute(cameraNode, "far", attr)) { rv.setFar(attr); }

		if (getValue(cameraNode, _values)) {

			rv.setEye(Vec3f(_values[0], _values[1], _values[2]));
			rv.setLookAt(Vec3f(_values[3], _values[4], _values[5]));
			rv.setup(Vec3f(_values[6], _values[7], _values[8]));
		}
		rv.computeAspectRatio(getWindowWidth(), getWindowHeight());
	}
	return rv;
}