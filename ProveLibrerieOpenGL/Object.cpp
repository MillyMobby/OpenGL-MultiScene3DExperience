#include "Object.h"
#include<iostream>
#include "Object.h"
#include<iostream>



void Object::setName(const std::string& name) { //MODIFICATAA ERA VUOTA
	_name = name;
}


const std::string& Object::getName() const {
	return _name;
}

void Object::setMatName(const std::string& matName) {
	_matName = matName;
}

const std::string& Object::getMatName() const {
	return _matName;
}

void Object::setVisible(bool isVisible) {
	_visible = isVisible;
}

bool Object::isVisible() {
	return _visible;
}


void Object::setMesh(Mesh m) {
	_mesh = m;
}


Mesh& Object::getMesh() {
	return _mesh;
}

void Object::setModelMatrix(Mat4f model) {

	_modelMatrix = model;
}


Mat4f Object::getModelMatrix() const {

	return _modelMatrix;
}


const std::string Object::getPath() const {
	return _path;
}

void Object::setPath(std::string path) { // NEW PER ASSIMP
	_path = path;
}

Vec4f Object::getPosition() {

	return getModelMatrix() * Vec4f(getMesh().getVertices().at(0), getMesh().getVertices().at(1), getMesh().getVertices().at(2), 1.0); // prendo uno qualsiasi dei suai vertici
}

void Object::setRot(bool rotates) {
	_rotates = rotates;
}
bool Object::rotates() {
	return _rotates;
}


Object Object::loadFromFile(std::string filePath) {

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_CalcTangentSpace); // HO RIMOSSO | aiProcess_FlipUVs perch� gi� lo facciamo con stb_image

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return Object();
	}

	//std::string directory = filePath.substr(0, filePath.find_last_of('/')); // NON HOP CAPITO A CHE CI SERVE

	aiNode* rootNode = scene->mRootNode;
	return Object::processNode(rootNode, scene);

}



Object Object::processNode(aiNode* node, const aiScene* scene) { // NEW PER ASSIMP
	Object rv;

	if (node->mNumMeshes > 0) {
		rv.setMesh(Mesh::processMesh(scene->mMeshes[node->mMeshes[0]], scene));
	}

	// considero solo l'ultima
	for (size_t i = 0; i < node->mNumChildren; i++) {
		rv = processNode(node->mChildren[i], scene);
	}

	return rv;
}



bool Object::initGL() { // c'� qualcosa di strano... torna sempre true
	bool rv = true;
	_mesh.initGL();
	return rv;
}


void Object::draw() {
	if (_visible) {
		_mesh.draw();
	}
}