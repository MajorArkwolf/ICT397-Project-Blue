#pragma once

#include <vector>

#include "Controller/Engine/BaseState.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/EulerCamera.hpp"
#include "Controller/InputManager.hpp"
#include "Controller/Physics/BeAbstractPhysicsLibrary.hpp"
#include "Controller/Physics/BeConfig.hpp"
#include "Controller/Physics/BeDynamicWorld.hpp"
#include "Controller/TerrainManager.hpp"


class PrototypeScene : public BaseState {
public:
    PrototypeScene();
    ~PrototypeScene() override;

    auto display() -> void override;
    auto update(double t, double dt) -> void override;

    void Init() override;
    void unInit() override;

    double time = 0;
    
    void handleInputData(Controller::Input::InputData inputData) override;
    Camera camera;

private:
    std::vector<size_t> models;
    Renderer renderer;
    Controller::TerrainManager terrain = {};

    //SDLFIX SDL_Event &event
    void handleWindowEvent();

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;

    double getDeltaTime();

    BeSettings settings;
    glm::vec3  grav;
    BeDynamicWorld *world;
    BeAbstractPhysicsFactory *factory;
    BeAbstractPhysicsLibrary *physics;
    BeAbstractPhysics *cam;
    BeAbstractPhysics *body;
    BeAbstractPhysics *test;

};
