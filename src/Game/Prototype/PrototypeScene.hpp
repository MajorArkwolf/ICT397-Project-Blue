#pragma once

#include <vector>

#include "Controller/Engine/BaseState.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/EulerCamera.hpp"
#include "Controller/InputManager.hpp"

class PrototypeScene : public BaseState {
public:
    PrototypeScene();
    ~PrototypeScene() override = default;

    auto display() -> void override;
    auto update(double t, double dt) -> void override;

    void Init() override;
    void unInit() override;

    double time = 0;
    void handleInputData(Controller::Input::InputData inputData);

private:
    std::vector<size_t> models;
    Renderer renderer;
    Camera camera;

    void handleWindowEvent(SDL_Event &event);

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;

    double getDeltaTime();
};
