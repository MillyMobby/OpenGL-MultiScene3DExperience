#pragma once
#include "Material.h"
#include "Object.h"
#include "Texture.h"
#include "Light.h"
#include <unordered_map>

typedef std::unordered_map<std::string, Material> HashMaterial;
typedef std::pair<std::string, Material> HashMaterialPair;

typedef std::unordered_map<std::string, Object> HashObject;
typedef std::pair<std::string, Object> HashObjectPair;

typedef std::unordered_map<std::string, Texture> HashTexture;
typedef std::pair<std::string, Texture> HashTexturePair;


typedef std::unordered_map<std::string, Light> HashLight;
typedef std::pair<std::string, Light> HashLightPair;