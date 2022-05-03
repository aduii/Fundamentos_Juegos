#pragma once
#include <string>
#include "GLTexture.h"
#include "Texturecache.h"
using namespace std;

class ResourceManager
{
private:
	static TextureCache textureCache;
public:
	static GLTexture getTexture(std::string texturePath);
};

