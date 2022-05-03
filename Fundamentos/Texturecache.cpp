#include "Texturecache.h"
#include "ImageLoader.h"


TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
    /*std::map<std::string, GLTexture>::iterator it
        = textureMap.find(texturePath);*/
    auto it = textureMap.find(texturePath);
    if (it == textureMap.end()) {
        GLTexture texture = ImageLoader::loadPNG(texturePath);
        //std::pair<std::string, GLTexture> newPair(texturePath, texture);
        //textureMap.insert(newPair);
        textureMap[texturePath] = texture;
        return texture;
    }
    return it->second;
}
