#include "Renderer.hpp"

#include <functional>

#include "Controller/Engine/Engine.hpp"
#include "Model/Models/ModelManager.hpp"

Renderer::Renderer() {
    auto &engine = BlueEngine::Engine::get();
    string vs    = engine.basepath + "/res/shader/vertshader.vs";
    string fs    = engine.basepath + "/res/shader/fragshader.fs";
    shader       = new Shader(vs.c_str(), fs.c_str());
}
Renderer::~Renderer() = default;

void Renderer::addToDraw(const glm::mat4 &modelMesh, const size_t &modelID) {
    drawList().push_back(std::make_pair(modelMesh, modelID));
}

void Renderer::draw(const glm::mat4 &view, const glm::mat4 &projection) {
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    for (auto &m : drawList()) {
        shader->setMat4("model", m.first);
        ModelManager::Draw(m.second, shader);
    }
    drawList().clear();
}

auto Renderer::drawList() -> std::vector<std::pair<glm::mat4, size_t>> & {
    static std::vector<std::pair<glm::mat4, size_t>> m = {};
    return m;
}
