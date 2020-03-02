//
// Created by becky on 28/12/2019.
//

#ifndef PROJECT_BLUE_QUATERNIONCAMERA_HPP
#define PROJECT_BLUE_QUATERNIONCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <SDL2/SDL_opengl.h>

#include "InputManager.hpp"

class QuaternionCamera {
  public:
    glm::vec3 cameraUp;
    glm::vec3 cameraPosition;
    glm::vec3 cameraEye;
    glm::vec3 cameraRotation;
    glm::quat deltaQuaternion;

    QuaternionCamera();
    QuaternionCamera(glm::vec3 initPosition, glm::vec3 eyePosition, glm::vec3 deltaPosition);
    void CameraRotate(glm::vec3 rotationVector, glm::vec3 targetAxis,
                      float inputDegree);
    void CameraMove(InputManager::keyStates direction, double cameraSpeed,
                    float deltaTime, float fps);
    void Update(glm::vec3 inputVector, float deltaTime, float fps);

  private:
    double deadZone;

};

#endif // PROJECT_BLUE_QUATERNIONCAMERA_HPP
