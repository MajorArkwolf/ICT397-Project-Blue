#include "Mesh.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include "View/Renderer/OpenGL.hpp"


Mesh::Mesh(std::vector<Vertex> newVertices, std::vector<unsigned int> newIndices,
           std::vector<TextureB> newTextures) {
    this->vertices = std::move(newVertices);
    this->indices  = std::move(newIndices);
    this->textures = std::move(newTextures);
    View::OpenGL::SetupMesh(VAO, VBO, EBO, this->vertices, this->indices);
}

void Mesh::Draw(Shader& shader) {
    View::OpenGL::DrawModel(shader, VAO, textures, indices);
}
