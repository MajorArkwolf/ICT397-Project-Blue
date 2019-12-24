#include "ModelManager.hpp"

#include <map>

auto ModelManager::GetModelID(std::string filename) -> size_t {
    static std::map<std::string, size_t> nameToId = {};
    auto id                                       = nameToId.find(filename);
    if (id == nameToId.end()) { // file not loaded yet
        ModelRepo().push_back(Model(filename, false));
        nameToId.emplace(filename, ModelRepo().size() - 1);
        return ModelRepo().size() - 1;
    } else {
        return id->second;
    }
}

void ModelManager::Draw(size_t id, Shader *ourshader) {
    ModelRepo().at(id).Draw(*ourshader);
}

auto ModelManager::ModelRepo() -> std::vector<Model> & {
    static std::vector<Model> m = {};
    return m;
}
