#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "View/Renderer/shader.hpp"

using std::vector, std::string;

struct Vertex {
    glm::vec3 Position;
    glm::vec2 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id = 0;
    string type;
    string path;
};

class Mesh {
  public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex> newVerticies, vector<unsigned int> newIndicies,
         vector<Texture> newTextures);
    void Draw(Shader shader);

  private:
    unsigned int VBO, EBO;

    void setupMesh();
};
