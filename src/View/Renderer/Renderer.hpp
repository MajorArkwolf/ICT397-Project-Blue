#pragma once
#include <utility>
#include <vector>

#include "Model/Models/Mesh.hpp"
#include "Shader.hpp"

class Renderer {
  public:
    Renderer();
    ~Renderer();
    void draw(const glm::mat4 &view, const glm::mat4 &projection);
    static void addToDraw(const glm::mat4 &modelMesh, const size_t &modelID);
    static auto drawList() -> std::vector<std::pair<glm::mat4, size_t>> &;

  private:
    Shader *shader = nullptr;
};
