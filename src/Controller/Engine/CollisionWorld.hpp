#pragma once

#include <reactphysics3d.h>

class Rp3dCollisionWorld {
  public:
    bool TestAABBOverlap(rp3d::CollisionBody target1, rp3d::CollisionBody target2);
  private:
    rp3d::CollisionWorld *collisionWorld;
};
