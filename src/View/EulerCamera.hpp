#pragma once
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const double YAW         = -90.0;
const double PITCH       = 0.0;
const double SPEED       = 0.05;
const double SENSITIVITY = 0.1;
const double ZOOM        = 45.0;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Camera Attributes
    glm::dvec3 Position;
    glm::dvec3 Front;
    glm::dvec3 Up;
    glm::dvec3 Right;
    glm::dvec3 WorldUp;
    // Euler Angles
    double Yaw;
    double Pitch;
    // Camera options
    double MovementSpeed;
    double MouseSensitivity;
    double Zoom;

    // Constructor with vectors
    Camera(glm::dvec3 position = glm::dvec3(0.0f, 0.0f, 0.0f),
           glm::dvec3 up = glm::dvec3(0.0f, 1.0f, 0.0f), double yaw = YAW,
           double pitch = PITCH);
    // Constructor with scalar values
    Camera(double posX, double posY, double posZ, double upX, double upY,
           double upZ, double yaw, double pitch);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // Processes input received from any keyboard-like input system. Accepts input
    // parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, double deltaTime);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(double xoffset, double yoffset,
                              GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(double yoffset);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

