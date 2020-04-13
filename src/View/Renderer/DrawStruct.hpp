#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <vector>
#include <functional>

namespace View::Data {
    struct DrawItem {
        std::vector<unsigned int> &indices;
        std::vector<Texture> &textures;
        std::function<void()> setShader = nullptr;
        Shader* shader = nullptr;
        unsigned int VAO = 0;
    };
}