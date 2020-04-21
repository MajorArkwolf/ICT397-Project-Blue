#include "TerrainModel.hpp"

#include "Controller/Engine/Engine.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <Controller/Factory/GameAssetFactory.hpp>

Model::TerrainModel::TerrainModel() {
}

Model::TerrainModel::~TerrainModel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Model::TerrainModel::SetupModel(const std::vector<Blue::Vertex>& verticies) {
    BlueEngine::Engine::get().renderer.SetupTerrainModel(VAO, VBO, EBO, verticies, indicies);
}

void Model::TerrainModel::LoadShader(std::shared_ptr<Shader> newTerrain) {
    this->terrainShader = newTerrain;
}

void Model::TerrainModel::setHeightOffsets(float newSnowHeight, float newDirtHeight, float newGrassHeight, float newSandHeight) {
    this->snowHeight = newSnowHeight;
    this->dirtHeight = newDirtHeight;
    this->grassHeight = newGrassHeight;
    this->sandHeight = newSandHeight;
}

void Model::TerrainModel::setTextures(unsigned int& snowTex, unsigned int& grasstex, unsigned int& dirtTex, unsigned int& sandTex) {
    textures.resize(4);
    textures.at(0) = snowTex;
    textures.at(1) = grasstex;
    textures.at(2) = dirtTex;
    textures.at(3) = sandTex;

    terrainShader->use();
    terrainShader->setInt("texture1", 0);
    terrainShader->setInt("texture2", 1);
    terrainShader->setInt("texture3", 2);
    terrainShader->setInt("texture4", 3);
}

void Model::TerrainModel::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
    terrainShader->use();
    terrainShader->setMat4("projection", projection);
    terrainShader->setMat4("view", view);
    terrainShader->setMat4("model", glm::translate(model, position));   
    terrainShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    terrainShader->setVec3("lightPos", 1.0f, 400.0f, 1.0f);
    terrainShader->setVec3("viewPos", cameraPos);
    terrainShader->setFloat("tm_snowHeight", snowHeight);
    terrainShader->setFloat("tm_dirtHeight", dirtHeight);
    terrainShader->setFloat("tm_grassHeight", grassHeight);
    terrainShader->setFloat("tm_sandHeight", sandHeight);
    BlueEngine::Engine::get().renderer.DrawTerrain(VAO, textures, indicies);
    water.Draw(projection, view, cameraPos);
}

void Model::TerrainModel::AddToDraw() {
    auto &renderer = BlueEngine::Engine::get().renderer;
    auto chunkSize = Controller::Factory::get().terrain.GetChunkSize();
    std::function e = [&](const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos) {
        this->Draw(projection, view, cameraPos);
    };
    View::Data::DrawItem di;
    di.drawPointer = e;
    di.pos = position;
    di.pos.x += chunkSize / 2.0f;
    di.pos.z += chunkSize / 2.0f;
    renderer.AddToQue(di);
}
