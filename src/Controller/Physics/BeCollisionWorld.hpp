#pragma once

#include <reactphysics3d.h>
#include "BeCollisionBody.hpp"

class BeCollisionWorld {
  public:
    BeCollisionWorld();
    bool TestAABBOverlap(rp3d::CollisionBody target1, rp3d::CollisionBody target2);
    BeCollisionBody

  private:
    rp3d::CollisionWorld beCollisionWorld();
};
