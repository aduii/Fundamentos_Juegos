#pragma once
#include <map>
#include "GLTexture.h"
#include <string>

class TextureCache
{
private:
	std::map<std::string, GLTexture> textureMap;
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(std::string texturePath);

};

