#include "ModelManager.hpp"

#include <map>

auto ModelManager::GetModelID(const std::string& filename) -> size_t {
    static std::map<std::string, size_t> nameToId = {};
    auto id                                       = nameToId.find(filename);
    if (id == nameToId.end()) { // file not loaded yet
        ModelRepo().emplace_back(filename, false);
        nameToId.emplace(filename, ModelRepo().size() - 1);
        return ModelRepo().size() - 1;
    } else {
        return id->second;
    }
}

void ModelManager::Draw(size_t id, Shader *ourShader) {
    ModelRepo().at(id).Draw(*ourShader);
}

auto ModelManager::ModelRepo() -> std::vector<Model::Model> & {
    static std::vector<Model::Model> m = {};
    return m;
}
