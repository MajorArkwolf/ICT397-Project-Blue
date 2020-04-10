#pragma once
#include <vector>
#include "Model.hpp"
#include "View/Renderer/Shader.hpp"

class ModelManager {
  public:
    static auto GetModelID(std::string filename) -> size_t;

    static void Draw(size_t id, Shader *ourshader);

  private:
    static auto ModelRepo() -> std::vector<Model::Model> &;
};
