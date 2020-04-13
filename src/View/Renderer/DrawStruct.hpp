#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <vector>
#include <functional>

namespace View::Data {
    enum class ShaderModel {
        model,
        terrain,
        water
    };
    struct DrawItem {
        std::function<void()> draw = nullptr;
        Shader* shader = nullptr;
        unsigned int VAO = 0;
    };
}