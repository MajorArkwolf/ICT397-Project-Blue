#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Model/Models/DataTypes.hpp"
#include "View/Renderer/Shader.hpp"
#include "View/Renderer/DrawStruct.hpp"

class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureB> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> newVerticies, std::vector<unsigned int> newIndicies,
         std::vector<TextureB> newTextures);
    void Draw(Shader& shader);

  private:
    unsigned int VBO = 0, EBO = 0;
	void setupMesh();
};
