#pragma once
#include <string>

#include "Controller/Engine/LuaManager.hpp"
#include "Model/Models/ModelManager.hpp"
#include "Model/TextManager.hpp"
#include "Controller/TextureManager.hpp"

class ResourceManager {
  public:
    auto loadResources() -> void;
    auto insertString(std::string key, std::string value) -> void;
    auto getString(std::string key) -> std::string;
    auto getModelID(std::string filename) -> size_t;
    auto drawModel(size_t id, Shader *ourshader) -> void;

    static auto getInstance() -> ResourceManager &;

  private:
    TextManager textManager;
    ModelManager modelManager;
    ResourceManager();
    static auto loadModel(const std::string &filePath) -> void;
    static auto loadString(const std::string key) -> void;
    static auto loadTexture(const std::string filePath, const std::string textureName) -> void;
};
