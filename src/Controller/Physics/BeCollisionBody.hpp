#pragma once

#include <reactphysics3d.h>

#include "BeTransform.hpp"
#include "BeCollisionWorld.hpp"

class BeCollisionBody {
  public:
    BeCollisionBody(const BeTransform &targetTransform, const BeCollisionWorld &targetWorld, beBodyId targetId);

    void SetTransform(const BeTransform &targetTransform);
    BeTransform GetTransform();


  private:
    BeTransform transform;
    rp3d::CollisionBody beCollisionBody;


};
