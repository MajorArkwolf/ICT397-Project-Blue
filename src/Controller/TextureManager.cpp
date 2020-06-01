#include "TextureManager.hpp"

#include <iostream>
#include "stb_image.h"
#include "Controller/Engine/Engine.hpp"

bool TextureManager::loadTextureFromFile(const std::string& filePath, const std::string& texName) {
    auto &basePath = BlueEngine::Engine::get().basepath;
    auto path      = basePath + filePath;
    unsigned int textureID = 0;
    glGenTextures(1, &textureID);

    int width = 0, height = 0, nrComponents = 0;
    unsigned char *image = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (image) {
        GLenum format = 1;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(image);
    }
    textureMap.emplace(texName, Texture{textureID, height, width});

    return true;
}

Texture &TextureManager::getTexture(const std::string& texName) {
    if (textureMap.find(texName) != textureMap.end()) {
        return textureMap.at(texName);
    }
    return textureMap.at("missing");
}

Texture &TextureManager::getTexture(unsigned int id) {
    for (auto &n : textureMap) {
        if (n.second.TextureID == id) {
            return n.second;
        }
    }
    Texture temp = {0, 0, 0};
    return temp;
}

TextureManager::TextureManager() {}
