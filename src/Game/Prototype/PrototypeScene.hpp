#pragma once

#include <reactphysics3d.h>
#include <vector>

#include "Controller/InputManager.hpp"
#include "Controller/TerrainManager.hpp"
#include "Model/BaseState.hpp"
#include "View/EulerCamera.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/Renderer/Skybox.hpp"

/**
 * @class PrototypeScene
 */
class PrototypeScene : public BaseState {
  public:
    PrototypeScene();
    ~PrototypeScene() override;

    /**
     * @brief Calls all draw calls for the prototype scene
     */
    auto display() -> void override;

    /**
     * @brief Updates everything in the prototype scene
     * @param t Time since the program started
     * @param dt The delta time since the last frame
     */
    auto update(double t, double dt) -> void override;

        /**
     * @brief A seperate initialiser function, called by the constructor
     */
    void Init() override;

        /**
     * @brief Function that can be used to uninitialise the scene, called by the destructor
     */
    void unInit() override;

        /**
     * @brief Handles input data using a passed in InputData struct from the engine
     * @param inputData The input event to read from
     */
    void handleInputData(Controller::Input::InputData inputData, double deltatime) override;

    float GetHeightAt(glm::vec2);

    void GUIStart() override;

    void GUIEnd() override;

  private:
      ///The terrain manager for the prototype scene
    Controller::TerrainManager terrain = {};

    /// Handles a window resize event
    void handleWindowEvent();

    ///Boolean logic for the camera, soon to be deprecated
    bool moveForward  = false;
    /// Boolean logic for the camera, soon to be deprecated
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;
};
