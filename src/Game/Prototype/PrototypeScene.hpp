#pragma once

#include <vector>
#include <reactphysics3d.h>

#include "Model/BaseState.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/EulerCamera.hpp"
#include "Controller/InputManager.hpp"

#include "Controller/Physics/BeAbstractPhysicsFactory.hpp"
#include "Controller/Physics/BeAbstractPhysicsLibrary.hpp"
#include "Controller/Physics/BeConfig.hpp"
#include "Controller/Physics/BeDynamicWorld.hpp"
#include "Controller/Physics/BeMaterial.hpp"

#include "Controller/TerrainManager.hpp"
#include "View/Renderer/Skybox.hpp"


class PrototypeScene : public BaseState {
public:
    PrototypeScene();
    ~PrototypeScene() override;

    auto display() -> void override;
    auto update(double t, double dt) -> void override;

    void Init() override;
    void unInit() override;

    void handleInputData(Controller::Input::InputData inputData) override;
    View::Camera camera;

private:
    std::vector<Model::Model> models = {};
    Controller::TerrainManager terrain = {};
    void handleWindowEvent();
    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;

    double getDeltaTime();

};
