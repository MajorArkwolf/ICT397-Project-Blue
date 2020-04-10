#include "TerrainModel.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Model::TerrainModel::TerrainModel() {
}

Model::TerrainModel::~TerrainModel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Model::TerrainModel::SetupModel() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // TexCords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    glBindVertexArray(0);
}

void Model::TerrainModel::LoadShader(std::shared_ptr<Shader> newTerrain) {
    this->terrainShader = newTerrain;
}

void Model::TerrainModel::setTextures(unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4) {
    this->textureID = tex1;
    this->textureID2 = tex2;
    this->textureID3 = tex3;
    this->textureID4 = tex4;

    terrainShader->use();
    terrainShader->setInt("texture1", 0);
    terrainShader->setInt("texture2", 1);
    terrainShader->setInt("texture3", 2);
    terrainShader->setInt("texture4", 3);
}

void Model::TerrainModel::Draw(glm::mat4 projection, glm::mat4 view, const glm::dvec3& cameraPos) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureID3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureID4);
    terrainShader->use();
    terrainShader->setMat4("projection", projection);
    terrainShader->setMat4("view", view);
    terrainShader->setMat4("model", glm::translate(model, position));   
    terrainShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    terrainShader->setVec3("lightPos", 1.0f, 200.0f, 1.0f);
    terrainShader->setVec3("viewPos", cameraPos);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicie_size, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    water.Draw(projection, view, cameraPos);
}
