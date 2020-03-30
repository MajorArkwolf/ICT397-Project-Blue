#pragma once

#include "BeTransform.hpp"

namespace BeReact {
    class BeCollisionWorld;

    class BeCollisionBody {
      public:
        BeCollisionBody();
        BeCollisionBody(BeTransform targetTransform,
                        BeCollisionWorld *targetWorld, beBodyId targetId);

        void SetTransform(const BeTransform &targetTransform);
        BeTransform GetTransform();

        BeCollisionWorld GetWorld();

        // void AddShape();

        beBodyId GetId();

      private:
        beBodyId id;
        BeTransform transform;
        BeCollisionWorld *world;
        // rp3d::CollisionBody *beCollisionBody;
        void *collisionBodyRaw;
    };
}