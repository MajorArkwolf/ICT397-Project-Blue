#pragma once

#include <vector>

#include "Controller/Engine/BaseState.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/EulerCamera.hpp"


class PrototypeScene : public BaseState {
public:
    PrototypeScene();
    ~PrototypeScene() override = default;

    auto display() -> void override;
    auto update(double t, double dt) -> void override;

    void Init() override;
    void unInit() override;
    void handleInput(SDL_Event &event) override;

    double time = 0;

private:
    std::vector<size_t> models;
    Renderer renderer;
    Camera camera;

    void handleKeyRelease(SDL_Event &event);
    void handleKeyPress(SDL_Event &event);
    void handleWindowEvent(SDL_Event &event);
    void handleMouseMovement(SDL_Event &event);
    void handleMouseScroll(SDL_Event &event);

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;

    double getDeltaTime();
};
