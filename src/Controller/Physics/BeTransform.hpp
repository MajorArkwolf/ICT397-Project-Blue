#pragma once

#include <reactphysics3d.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeQuaternion.hpp"
#include "BeVector3.hpp"

class BeTransform {
  public:
    /**
     * @brief default constructor
     */
    BeTransform();

    /**
     * @brief parameterised constructor
     * @param position object position in physics world
     * @param orientation object rotation in physics world
     */
    BeTransform(BeVector3 position, BeQuaternion orientation);

    /**
     * @brief parameterised constructor
     * @param position object position in physics world
     * @param orientation object rotation in physics world
     */
    BeTransform(glm::vec3 position, glm::quat orientation);

    /**
     * @brief parameterised constructor
     * @param inputTransform position and rotation in physics world
     */
    BeTransform(const BeTransform &inputTransform);

    /**
     * @brief parameterised constructor
     * @param inputTransform position and rotation in physics world
     */
    BeTransform(const rp3d::Transform &inputTransform);

    /**
     * @brief destructor
     */
    ~BeTransform();

    /**
     * @brief sets physics object rotation
     * @param inputOrientation the rotation
     */
    void SetOrientation(BeQuaternion inputOrientation);

    /**
     * @param inputOrientation the rotation
     */
    BeQuaternion GetOrientation();

    /**
     * @brief Sets the physics object position
     * @param inputPosition the position
     */
    void SetPosition(const BeVector3 &inputPosition);

    /**
     * @brief gets the physics object position
     */
    glm::vec3 GetPosition() const;

    /**
     * @brief sets the orientation and position to identity
     */
    void SetToIdentity();

    /**
     * @brief gets the orientation and position inverse
     */
    BeTransform GetInverse();

    /**
     * @brief assignment operator
     * @param rhs target transform
     * @return target transform
     */
    BeTransform &operator=(const BeTransform &rhs);

    /**
     * @brief multiplications operator
     * @param rhs target transform
     * @return multiplied rotation and position
     */
    BeTransform &operator*(const BeTransform &rhs);

  private:
    rp3d::Quaternion orientation;
    rp3d::Vector3 position;
    rp3d::Transform transform;
};