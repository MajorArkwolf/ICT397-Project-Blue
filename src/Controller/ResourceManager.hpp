#pragma once
#include <string>

#include "Controller/Engine/LuaManager.hpp"
#include "Model/Models/ModelManager.hpp"
#include "Model/TextManager.hpp"

class ResourceManager {
  public:
    void loadResources();


  private:
    static auto getInstance() -> ResourceManager &;
    TextManager textManager;
    ModelManager modelManager;
    ResourceManager();
    static void loadModel(const std::string &filePath);
    static void loadString(const std::string key);

};