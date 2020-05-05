#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Bitangent;
    glm::vec3 Tangent;
    glm::vec2 Normal;
    glm::vec2 TexCoords;
};

struct TextureB {
    std::string type;
    std::string path;
    unsigned int id = 0;
};
