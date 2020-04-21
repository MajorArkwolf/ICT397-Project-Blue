#include "WaterModel.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <utility>


Model::Water::Water() {

}

void Model::Water::SetupModel(const std::vector<Blue::Vertex>& verticies) {
    BlueEngine::Engine::get().renderer.SetupTerrainModel(VAO, VBO, EBO, verticies, indicies);
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
    BlueEngine::Engine::get().renderer.DrawTerrain(VAO, textures, indicies);
}

void Model::Water::SetTexture(unsigned int newTex) {
    waterTextureID = newTex;
    textures.resize(1);
    textures.at(0) = waterTextureID;
}

void Model::Water::SetWaterHeight(float newWaterHeight) {
    position.y = newWaterHeight;
}
