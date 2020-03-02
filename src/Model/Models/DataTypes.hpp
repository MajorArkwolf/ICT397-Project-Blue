#pragma once

struct Vertex {
    glm::vec3 Position;
    glm::vec2 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id = 0;
    std::string type;
    std::string path;
};
