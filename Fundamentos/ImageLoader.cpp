#include "ImageLoader.h"
#include "IOManager.h"
#include "Error.h"
#include "picoPNG.h"


GLTexture ImageLoader::loadPNG(std::string filePath)
{
    GLTexture texture = {};
    std::vector<unsigned char> out;
    std::vector<unsigned char> in;
    unsigned long widht, height;

    if (!IOManager::readFileToBuffer(filePath, in)) {
        fatalError("No se puede leer el archivo " + filePath);
    }
    int errorCode = decodePNG(out, widht, height, &(in[0]), in.size());
    if (errorCode != 0) {
        fatalError("No se puede decodear la imagen " + std::to_string(errorCode));
    }
    glGenTextures(1, &(texture.id));
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widht, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture.width = widht;
    texture.height = height;
    return texture;
}
