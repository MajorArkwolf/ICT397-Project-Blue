#pragma once
#include <memory>
#include "View/Renderer/Shader.hpp"
class PlayerCanvas {
public:

    PlayerCanvas();

    void update(double t, double dt);

    void draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);

    void addToDraw();
private:
    float height = 0.0f;
    std::unique_ptr<Shader> shader = nullptr;
};

