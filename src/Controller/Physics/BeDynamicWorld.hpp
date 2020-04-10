#pragma once

#include <reactphysics3d.h>
#include <glm/glm.hpp>

#include "BeConfig.hpp"

class BeAbstractPhysics;

class BeDynamicWorld {

  public:

    /**
     *  @brief parameterised constructor
     *  @param worldSettings the settings of the world
     *  @return
     */
    BeDynamicWorld();

    /**
     *  @brief parameterised constructor
     *  @param worldSettings the settings of the world
     *  @return
     */
    BeDynamicWorld(const glm::vec3 &gravity, const BeSettings &settings);


    /**
     *  @brief Getter for gravity
     *  @param
     *  @return gravity for the world
     */
    glm::vec3 GetGravity();


    /**
     *  @brief creates a collision body with the world's settings
     *  @param transform the position of the body
     *  @return a collision body
     */
    rp3d::RigidBody *CreateRigidBody(rp3d::Transform transform);

    /**
     *  @brief AABB collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestAABBOverlap(rp3d::RigidBody *body1, rp3d::RigidBody *body2);

    /**
     *  @brief AABB collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestAABBOverlap(BeAbstractPhysics *target1, BeAbstractPhysics *target2);

    /**
     *  @brief collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestOverLap(rp3d::RigidBody *body1, rp3d::RigidBody *body2);

    /**
     *  @brief collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestOverLap(BeAbstractPhysics *target1, BeAbstractPhysics *target2);

  private:
    BeSettings worldSettings;
    rp3d::Vector3 *worldGravity;
    rp3d::DynamicsWorld *bePhysicsWorld;
};
