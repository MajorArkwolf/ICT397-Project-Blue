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
        glm::vec3 pos = {};
        std::function<void(glm::mat4 projection, glm::mat4 view, const glm::dvec3& cameraPos)> draw = nullptr;
    };
}