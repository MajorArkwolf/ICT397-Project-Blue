
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
    std::cout << scriptPath;
    luaL_dofile(L, scriptPath.c_str());
    lua_pcall(L, 0, 0, 0);

}

auto ResourceManager::insertString(std::string key, std::string value) -> void {
    TextManager::InsertString(key, value);
}

auto ResourceManager::getString(std::string key) -> std::string {
    return TextManager::GetString(key);
}

auto ResourceManager::getModelID(std::string filename) -> size_t {
    return ModelManager::GetModelID(filename);
}

auto ResourceManager::drawModel(size_t id, Shader *ourshader) -> void {
    ModelManager::Draw(id, ourshader);
}

void ResourceManager::loadModel(const std::string &filePath) {
    ModelManager::GetModelID(filePath);
}

void ResourceManager::loadString(const std::string key) {
    using namespace luabridge;

    auto *L     = LuaManager::getInstance().getLuaState();
    static luabridge::LuaRef stringTable(L);

    if (stringTable.isNil()) {
        stringTable = getGlobal(L, "Strings");
        if (stringTable.isNil()) {
            std::cout << "Failed to load 'Strings' table from LoadResources.lua\n";
            assert(!stringTable.isNil());
        }

    }

    LuaRef text = stringTable[key.c_str()];

    if (text.isString()) {
        TextManager::InsertString(key, text.cast<std::string>());
    } else {
        std::cout << "Failed to load string with id \"" << key << "\"\n";
    }
}
