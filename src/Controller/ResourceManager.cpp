
#include "ResourceManager.hpp"

#include "Controller/Engine/Engine.hpp"

auto ResourceManager::getInstance() -> ResourceManager & {
    static auto instance = ResourceManager{};

    return instance;
}

ResourceManager::ResourceManager() {}

void ResourceManager::loadResources() {
    using namespace luabridge;
    auto *L        = LuaManager::getInstance().getLuaState();
    auto &basePath = BlueEngine::Engine::get().basepath;

    auto scriptPath = basePath + "res/scripts/LoadResources.lua";
    getGlobalNamespace(L).beginNamespace("resources").addFunction("loadString", &loadString).endNamespace();
    getGlobalNamespace(L).beginNamespace("resources").addFunction("loadModel", &loadModel).endNamespace();

    luaL_dofile(L, scriptPath.c_str());
    lua_pcall(L, 0, 0, 0);

}

void ResourceManager::loadModel(const std::string &filePath) {
    ModelManager::GetModelID(filePath);
}

void ResourceManager::loadString(const std::string key) {
    using namespace luabridge;

    auto *L     = LuaManager::getInstance().getLuaState();
    static luabridge::LuaRef stringTable(L);

    if (stringTable.isNil()) {
        std::cout << "string table nil \n";
        stringTable = getGlobal(L, "Strings");
        if (stringTable.isNil()) {
            assert(!stringTable.isNil(), "LoadResources.lua must contain a string table");
        }

    }

    LuaRef text = stringTable[key.c_str()];
    if (text.isString()) {
        TextManager::InsertString(key, text.cast<std::string>());
    }
}
