#include "PlayerCanvas.hpp"
#include <functional>
#include <View/Renderer/DrawStruct.hpp>
#include <Controller/Engine/Engine.hpp>

PlayerCanvas::PlayerCanvas() {
    shader = std::make_unique<Shader>("res/shader/playercanvas.vs", "res/shader/playercanvas.vs");
}

void PlayerCanvas::update(double t, double dt) {

}

void PlayerCanvas::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos) {

}

void PlayerCanvas::addToDraw() {
    // Create a function pointer of the GameObject's draw call for the DrawItem
    std::function<void(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos)> e = [&](const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
        this->draw(projection, view, cameraPos);
    };

    // Here the DrawItem for the GameObject is generated and configured
    View::Data::DrawItem drawItem = {};
    drawItem.drawPointer = e;

    // Finally the DrawItem is added to the renderer queue
    auto& renderer = BlueEngine::Engine::get().renderer;
    renderer.AddToQue(drawItem);
}
