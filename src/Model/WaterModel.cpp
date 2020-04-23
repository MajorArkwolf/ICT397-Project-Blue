#include "WaterModel.hpp"
#include <utility>

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
    auto temp = model;
    temp = glm::translate(temp, position);
    //temp = glm::scale(temp, scale);
    shader->use();
    shader->setMat4("w_projection", projection);
    shader->setMat4("w_view", view);
    shader->setMat4("w_model", temp);
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", 1.0f, 400.0f, 1.0f);
    shader->setVec3("viewPos", cameraPos);
    BlueEngine::Engine::get().renderer.DrawTerrain(VAO, textures, EBO_Size);
}

void Model::Water::SetTexture(unsigned int newTex) {
    textures.resize(1);
    textures.at(0) = newTex;
}

void Model::Water::SetWaterHeight(float newWaterHeight) {
    position.y = newWaterHeight;
}
