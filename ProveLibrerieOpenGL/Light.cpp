#include "Light.h"

void Light::setName(std::string name)
{
	_name = name;
}

void Light::setPosition(Vec3f pos) {
	_position = pos;
}

void Light::setColor(Vec3f color) {
	_color = color;
}

void Light::setLookAt(Vec3f lookAt) {
	_lookAt = lookAt;
}

void Light::setEnable(bool enable) {
	_enable = enable;
}

void Light::setDirection(Vec3f dir) {
	_direction = dir;
}

void Light::setTheta(const float& angle) {
	_theta = angle;
}

void Light::setKc(const float& k) { 
	_kc = k;
}

void Light::setType(std::string& t)
{
	_type = t;
}

float Light::getKc() const {
	return _kc;
}

std::string Light::getType() const
{
	return _type;
}

void Light::setK1(const float& k) { 
	_k1 = k;
}

float Light::getK1() const {
	return _k1;
}

void Light::setKq(const float& k) { 
	_kq = k;
}

float Light::getKq() const {
	return _kq;
}

float Light::getTheta() const {
	return _theta;
}


std::string Light::getName() const {
	return _name;
}

Vec4f Light::getPosition() const {
	return Vec4f(_position, 1.0);
}

Vec3f Light::getColor() const {
	return _color;
}

Vec3f Light::getLookAt() const {
	return _lookAt;
}



Vec4f Light::getWCL() { // nel caso non sia un faretto distunguo la posizione e la direzione dall'ultimo valore
	if (_direction.length() != 0) { // se la luce ha una direzione
		//std::cout << "sto dando la direzione " << std::endl;
		return Vec4f(_direction.x, _direction.y, _direction.z, 0.0);
	}
	else if (_position.length() != 0) { // la luce ha solo una posizione
		//std::cout << "sto dando la pozizione " << std::endl;
		return Vec4f(_position.x, _position.y, _position.z, 1.0);
	}
	else {
		return Vec4f(-1, -1, -1, -1);
		std::cout << "ATTENZIONE: non è stata messa ne una posizione della luce ne una posizione => la luce e' ambientale" << std::endl;
	}
}


Vec4f Light::getDirection() {
	return Vec4f(_direction, 0.0);
}

bool Light::isEnable() const {
	return _enable;
}

void Light::setAmbientFactor(const float& f) {
	_ambientFactor = f;
}

float Light::getAmbientFactor() const {
	return _ambientFactor;
}