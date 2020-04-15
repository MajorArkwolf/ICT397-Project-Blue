#pragma once

#include <iostream>
#include <reactphysics3d.h>

#include "BeConfig.hpp"

class BeAbstractCollision;

class BeCollisionWorld {
  public:
    /**
     *  @brief default constructor
     *  @param
     *  @return
     */
    BeCollisionWorld();

    /**
     *  @brief parameterised constructor
     *  @param worldSettings the settings of the world
     *  @return
     */
    BeCollisionWorld(const BeSettings &worldSettings);

    /**
     * @brief destructor fro world
     */
    ~BeCollisionWorld();

    /**
     *  @brief Getter for config
     *  @param
     *  @return settings for the world
     */
    BeSettings GetConfig();

    /**
     *  @brief creates a collision body with the world's settings
     *  @param transform the position of the body
     *  @return a collision body
     */
    rp3d::CollisionBody *CreateCollisionBody(rp3d::Transform transform);

    /**
     *  @brief AABB collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestAABBOverlap(rp3d::CollisionBody *body1, rp3d::CollisionBody *body2);

    /**
     *  @brief AABB collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestAABBOverlap(BeAbstractCollision *target1, BeAbstractCollision *target2);

    /**
     *  @brief collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestOverLap(rp3d::CollisionBody *body1, rp3d::CollisionBody *body2);

    /**
     *  @brief collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @return boolean of whether an object intersects with another
     */
    bool TestOverLap(BeAbstractCollision *target1, BeAbstractCollision *target2);

    /**
     *  @brief delete body
     *  @param body collision body
     *  @return
     */
    void DestroyCollisionBody(rp3d::CollisionBody *body);

  private:
    BeSettings beConfig;
    rp3d::CollisionWorld *beCollisionWorld;
};
