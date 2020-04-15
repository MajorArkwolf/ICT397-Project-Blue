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
     * @brief destructor for world
     */
    ~BeDynamicWorld();

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

    /**
     *  @brief delete body
     *  @param body rigid body
     *  @return
     */
    void DestroyRigidBody(rp3d::RigidBody *body);

    /**
     *  @brief gravity toggle
     *  @param toggle boolean for switching on gravity
     *  @return
     */
    void EnableGravity(bool toggle);

    /**
     *  @brief delete body
     *  @param gravity the gravity constant
     *  @return
     */
    void SetGravity(glm::vec3 gravity);

    /**
     *  @brief sleeping toggle where objects come to rest
     *  @param toggle boolean for switching on sleep
     *  @return
     */
    void EnableSleeping(bool toggle);

    /**
     *  @brief set resting velocity
     *  @param velocity speed
     *  @return
     */
    void SetSleepLinearVelocity(float velocity);

    /**
     *  @brief set angular velocity
     *  @param velocity speed
     *  @return
     */
    void SetSleepAngularVelocity(float velocity);

    /**
     * @brief sets the number of iterations to solve for new position
     * @param iterations number of tries
     */
    void SetNumIterationPositionSolver(int iterations);

    /**
     * @brief sets the number of iterations to solve for new position
     * @param iterations number of tries
     */
    void SetNumIterationVelocitySolver(int iterations);

  private:
    BeSettings worldSettings;
    rp3d::Vector3 *worldGravity;
    rp3d::DynamicsWorld *bePhysicsWorld;
};
