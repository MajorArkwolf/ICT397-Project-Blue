//
// Created by Arkwolf on 19/12/2019.
//

#ifndef PROJECT_BLUE_PROTOTYPESCENE_HPP
#define PROJECT_BLUE_PROTOTYPESCENE_HPP

#include <vector>

#include <Engine/BaseState.hpp>
#include "Renderer/Renderer.hpp"
#include "Engine/EulerCamera.hpp"


class PrototypeScene : public BaseState {
public:
    PrototypeScene();
    ~PrototypeScene() override = default;

    auto display() -> void override;
    auto update(double dt) -> void override;

    void hardInit() override;
    void softInit() override;
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

    int width  = 0;
    int height = 0;
    int ratio  = 0;

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;

    double getDeltaTime();
};


#endif //PROJECT_BLUE_PROTOTYPESCENE_HPP
