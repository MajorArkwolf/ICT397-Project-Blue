#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Model/Models/DataTypes.hpp"
#include "View/Renderer/shader.hpp"

class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> newVerticies, std::vector<unsigned int> newIndicies,
         std::vector<Texture> newTextures);
    void Draw(Shader shader);

  private:
    unsigned int VBO, EBO;

    void setupMesh();
};
