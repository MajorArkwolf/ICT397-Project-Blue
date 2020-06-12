
#include "ResourceManager.hpp"

#include "Controller/Engine/Engine.hpp"

auto ResourceManager::getInstance() -> ResourceManager & {
    static auto instance = ResourceManager{};

    return instance;
}

TextManager &ResourceManager::GetTextManager() {
    return textManager;
}

ModelManager &ResourceManager::GetModelManager() {
    return modelManager;
}

TextureManager &ResourceManager::GetTextureManager() {
    return textureManager;
}

ResourceManager::ResourceManager() {}

void ResourceManager::loadResources() {
    using namespace luabridge;
    auto *L        = LuaManager::getInstance().getLuaState();
    auto &basePath = BlueEngine::Engine::get().basepath;

    const auto scriptPath = basePath + "res/scripts/LoadResources.lua";
    getGlobalNamespace(L)
        .beginNamespace("resources")
        .addFunction("loadString", &loadString)
        .addFunction("loadModel", &loadModel)
        .addFunction("loadTexture", &loadTexture)
        .addFunction("getModel", &getModelId)
        .endNamespace();
    luaL_dofile(L, scriptPath.c_str());
    lua_pcall(L, 0, 0, 0);
}

auto ResourceManager::insertString(const std::string& key, const std::string& value) -> void {
    TextManager::InsertString(key, value);
}

auto ResourceManager::getString(const std::string& key) -> std::string {
    return TextManager::GetString(key);
}

auto ResourceManager::getModelID(const std::string& filename) -> size_t {
    return modelManager.GetModelID(filename);
}

auto ResourceManager::drawModel(size_t id, Shader *ourshader) -> void {
    modelManager.Draw(id, ourshader);
}

void ResourceManager::loadModel(const std::string &filePath) {
    ResourceManager::getInstance().modelManager.GetModelID(filePath);
}

void ResourceManager::loadString(const std::string& key) {
    using namespace luabridge;

    auto *L = LuaManager::getInstance().getLuaState();
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

auto ResourceManager::loadTexture(const std::string& filePath, const std::string& textureName) -> void {
    getInstance().textureManager.loadTextureFromFile(filePath, textureName);
}

auto ResourceManager::getModelId(const std::string& key) -> size_t {

    return getInstance().getModelID(key);
}
auto ResourceManager::getModel(const size_t modelID) -> Model::Model* {
    return getInstance().modelManager.getModel(modelID);
}
