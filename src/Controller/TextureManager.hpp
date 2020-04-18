#pragma once
#include "Model/Texture.hpp"
#include "stb_image.h"
#include <map>

class TextureManager {


  public:
    bool loadTextureFromFile(std::string filePath, std::string texName);
    Texture& getTexture(std::string texName);
    static TextureManager& getInstance();
    std::map<std::string, Texture> textureMap;
    void reloadTexture(std::string textureName);
  private:
    TextureManager();


};