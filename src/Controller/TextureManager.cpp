#include "TextureManager.hpp"

#include <iostream>

#include "Controller/Engine/Engine.hpp"

bool TextureManager::loadTextureFromFile(std::string filePath, std::string texName) {
    int width  = 0;
    int height = 0;

    auto &basePath = BlueEngine::Engine::get().basepath;
    auto path      = basePath + filePath;

    unsigned char *image = stbi_load(path.c_str(), &width, &height, nullptr, 4);

    if (image == nullptr) {
        std::cout << "Image not found at \"" << path << "\"\n";
        return false;
    }

    // Create an opengl texture id
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    //Free memory
    stbi_image_free(image);

    textureMap.emplace(texName, Texture{textureID, height, width});

    return true;
}

Texture &TextureManager::getTexture(std::string texName) {
    return textureMap.at(texName);
}

TextureManager &TextureManager::getInstance() {
    static auto instance = TextureManager{};

    return instance;
}

TextureManager::TextureManager() {}
