#include "Mesh.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "View/Renderer/OpenGL.hpp"


Mesh::Mesh(std::vector<Vertex> newVerticies, std::vector<unsigned int> newIndicies,
           std::vector<TextureB> newTextures) {
    this->vertices = newVerticies;
    this->indices  = newIndicies;
    this->textures = newTextures;
    View::OpenGL::SetupMesh(VAO, VBO, EBO, this->vertices, this->indices);
    //drawItem.shader
}

void Mesh::Draw(Shader& shader) {
    View::OpenGL::DrawModel(shader, VAO, textures, indices);
}
