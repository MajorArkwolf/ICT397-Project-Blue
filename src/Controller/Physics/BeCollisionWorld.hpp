#pragma once

#include <reactphysics3d.h>

#include "BeConfig.hpp"

class BeAbstractBody;

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
     *  @param worldSettings the world settings
     *  @return boolean of whether an object intersects with another
     */
    bool TestAABBOverlap(BeAbstractBody *target1, BeAbstractBody *target2,
                         BeSettings worldSettings);

    /**
     *  @brief collision detector
     *  @param target1 collision body
     *  @param target2 collision body
     *  @param worldSettings the world settings
     *  @return boolean of whether an object intersects with another
     */
    bool TestOverLap(BeAbstractBody *target1, BeAbstractBody *target2,
                     BeSettings worldSettings);

  private:
    BeSettings beConfig;
    rp3d::CollisionWorld *beCollisionWorld;
};
