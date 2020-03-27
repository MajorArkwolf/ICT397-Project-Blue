#pragma once

#include <reactphysics3d.h>

#include "BeTransform.hpp"
#include "BeCollisionWorld.hpp"

class BeCollisionBody {
  public:
    BeCollisionBody(BeTransform targetTransform, BeCollisionWorld targetWorld, beBodyId targetId);

    void SetTransform(const BeTransform &targetTransform);
    BeTransform GetTransform();


  private:
    BeTransform transform;
    rp3d::CollisionBody *beCollisionBody;


};
