#pragma once

#include <reactphysics3d.h>

#include "BeConfig.hpp"

class BeAbstractBody;

class BeCollisionWorld {
  public:
    BeCollisionWorld();
    BeCollisionWorld(const BeSettings &worldSettings);
    BeSettings GetConfig();

    rp3d::CollisionBody *CreateCollisionBody(rp3d::Transform transform);

    bool TestAABBOverlap(BeAbstractBody *target1, BeAbstractBody *target2,
                         BeSettings worldSettings);
    bool TestOverLap(BeAbstractBody *target1, BeAbstractBody *target2,
                     BeSettings worldSettings);

  private:
    BeSettings beConfig;
    rp3d::CollisionWorld *beCollisionWorld;
};
