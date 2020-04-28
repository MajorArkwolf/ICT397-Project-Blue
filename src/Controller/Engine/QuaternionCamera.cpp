#include "QuaternionCamera.hpp"

QuaternionCamera::QuaternionCamera() {
    cameraUp        = glm::vec3(0, 0, 0);
    cameraPosition  = glm::vec3(0, 0, 0);
    cameraEye       = glm::vec3(0, 0, 0);
    cameraRotation  = glm::vec3(0, 0, 0);
    deltaQuaternion = glm::quat(1, 0, 0, 0);
}

QuaternionCamera::QuaternionCamera(glm::vec3 initPosition, glm::vec3 eyePosition,
                     glm::vec3 deltaPosition) {

    cameraUp       = glm::vec3(0, 1, 0);
    cameraPosition = initPosition;
    cameraEye      = eyePosition;
    cameraRotation = deltaPosition;
    deltaQuaternion = glm::quat(1, 0, 0, 0);
}

void QuaternionCamera::CameraRotate(glm::vec3 rotationVector, glm::vec3 targetAxis,
                                float inputDegree) {

    float radians = glm::radians(inputDegree);
    deltaQuaternion =
        glm::quat(0, rotationVector.x, rotationVector.y, rotationVector.z);
    glm::quat resultQuaternion = glm::rotate(deltaQuaternion, radians, targetAxis);
    cameraRotation =
        glm::vec3(resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
}

void QuaternionCamera::CameraMove(InputManager::keyStates direction,
                              double cameraSpeed, float deltaTime, float fps) {

    glm::vec3 unitRotation = glm::normalize(cameraRotation);
    float scalar           = cameraSpeed * deltaTime * fps;

    if (direction == InputManager::Forward) {
        cameraPosition += unitRotation * scalar;
    }

    if (direction == InputManager::Backward) {
        cameraPosition -= unitRotation * scalar;
    }

    if (direction == InputManager::Right) {
        cameraPosition +=
            glm::normalize(glm::cross(cameraUp, unitRotation)) * scalar;
    }

    if (direction == InputManager::Left) {
        cameraPosition -=
            glm::normalize(glm::cross(cameraUp, unitRotation)) * scalar;
     }
}

void QuaternionCamera::Update(glm::vec3 inputVector, float deltaTime, float fps) {
    // calculate pitch axis for rotating, therefore the orthogonal between the
    // forward and up assuming righthandedness
    if (abs(inputVector.length()) > 0) {
        CameraRotate(cameraRotation,
                     glm::normalize(glm::cross(cameraUp, cameraRotation)),
                     inputVector.y);
        CameraRotate(cameraRotation, cameraUp, inputVector.x);
    }

    cameraEye = cameraPosition + cameraRotation;
}
