#include "WaterModel.hpp"
#include <utility>
#include <Controller/Factory/GameAssetFactory.hpp>

void Model::Water::SetupModel(const std::vector<Blue::Vertex> &vertices,
                              const std::vector<unsigned int> &indices) {
    BlueEngine::Engine::get().renderer.SetupTerrainModel(VAO, VBO, EBO, vertices, indices);
    this->EBO_Size = static_cast<unsigned int>(indices.size());
}

void Model::Water::SetShader(std::shared_ptr<Shader> newWater) {
    shader = std::move(newWater);
    shader->use();
    shader->setInt("texture1", 0);
}

void Model::Water::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
    auto &engine = BlueEngine::Engine::get();
    auto temp = model;
    temp = glm::translate(temp, position);
    //temp = glm::scale(temp, scale);
    shader->use();
    shader->setFloat("w_time", static_cast<float>(engine.getT()));
    shader->setMat4("w_projection", projection);
    shader->setMat4("w_view", view);
    shader->setMat4("w_model", temp);
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", 1.0f, 400.0f, 1.0f);
    shader->setVec3("viewPos", cameraPos);
    engine.renderer.DrawTerrain(VAO, textures, EBO_Size);
}

void Model::Water::SetTexture(unsigned int newTex) {
    textures.resize(1);
    textures.at(0) = newTex;
}

void Model::Water::SetWaterHeight(float newWaterHeight) {
    position.y = newWaterHeight;
}

void Model::Water::AddToDraw() {
    auto &renderer = BlueEngine::Engine::get().renderer;
    auto chunkSize = Controller::Factory::get().terrain.GetChunkSize();
    std::function<void(const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos)> e = [&](const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos) {
        this->Draw(projection, view, cameraPos);
    };
    View::Data::DrawItem di = {};
    di.drawPointer = e;
    di.pos = position;
    di.pos.x += chunkSize / 2.0f;
    di.pos.z += chunkSize / 2.0f;
    renderer.AddToQue(di);
}
