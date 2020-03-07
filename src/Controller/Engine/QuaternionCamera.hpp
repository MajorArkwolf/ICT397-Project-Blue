
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "InputManager.hpp"

class QuaternionCamera {
  private:
    glm::vec3 cameraUp;
    glm::vec3 cameraPosition;
    glm::vec3 cameraEye;
    glm::vec3 cameraRotation;
    glm::quat deltaQuaternion;

  public:
    /**
     *  @brief default camera constructor
     *  @param
     *  @return
     */
    QuaternionCamera();

    /**
     *  @brief camera constructor
     *  @param initPosition initial camera position
     *  @param eyePosition initial view position
     *  @param deltaPosition initial rotation position
     *  @return
     */
    QuaternionCamera(glm::vec3 initPosition, glm::vec3 eyePosition, glm::vec3 deltaPosition);

    /**
     *  @brief rotating the camera using quaternion math
     *  @param rotationVector the "front" vector
     *  @param targetAxis the axis to rotate around
     *  @param inputDegree degree rotation to rotate by
     *  @return void
     */
    void CameraRotate(glm::vec3 rotationVector, glm::vec3 targetAxis,
                      float inputDegree);

    /**
     *  @brief moves the camera position in game space
     *  @param direction the movement in x direction
     *  @param cameraSpeed the speed which the camera moves
     *  @param deltaTime game time elapsed
     *  @param fps frames per second
     *  @return void
     */
    void CameraMove(InputManager::keyStates direction, double cameraSpeed,
                    float deltaTime, float fps);

    /**
    *  @brief update camera properties in the game
    *  @param inputVector degree movement for rotation
    *  @param deltaTime game time elapsed
    *  @param fps frames per second
    *  @return void
    */
    void Update(glm::vec3 inputVector, float deltaTime, float fps);
};

