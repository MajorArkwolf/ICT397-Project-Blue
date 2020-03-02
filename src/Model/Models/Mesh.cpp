#include "Mesh.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "View/Renderer/OpenGLProxy.hpp"


Mesh::Mesh(std::vector<Vertex> newVerticies, std::vector<unsigned int> newIndicies,
           std::vector<Texture> newTextures) {
    this->vertices = newVerticies;
    this->indices  = newIndicies;
    this->textures = newTextures;
    BlueEngine::RenderCode::SetupMesh(VAO, VBO, EBO, this->vertices, this->indices);

    //setupMesh();
}

void Mesh::Draw(Shader shader) {
    BlueEngine::RenderCode::DrawModel(shader, VAO, textures, indices);
}
