#pragma once

#include <reactphysics3d.h>

#include "BeTransform.hpp"

class BeCollisionWorld;

class BeCollisionBody {
  public:
    BeCollisionBody();
    BeCollisionBody(BeTransform targetTransform, BeCollisionWorld *targetWorld,
                    beBodyId targetId);

    void SetTransform(const BeTransform &targetTransform);
    BeTransform GetTransform();

    BeCollisionWorld *GetWorld();

    beBodyId GetId();

  private:
    beBodyId id;
    BeTransform transform;
    BeCollisionWorld *world;
    // rp3d::CollisionBody *beCollisionBody;
    void *collisionBodyRaw;
};
