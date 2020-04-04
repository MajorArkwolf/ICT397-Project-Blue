#pragma once

#include <reactphysics3d.h>
#include "BeConfig.hpp"

namespace BeReact {
    class BeCollisionBody;

    class BeCollisionWorld {
      public:
        BeCollisionWorld();
        BeCollisionWorld(const BeSettings &worldSettings);
        BeSettings GetConfig();

        BeCollisionBody *CreateCollisionBody(rp3d::Transform transform);

        bool TestAABBOverlap(BeReact::BeCollisionBody *target1,
                             BeReact::BeCollisionBody *target2,
                             BeSettings worldSettings);
        bool TestOverLap(BeReact::BeCollisionBody target1,
                         BeReact::BeCollisionBody target2,
                         BeSettings worldSettings);

      private:
        BeSettings beConfig;
        rp3d::CollisionWorld *beCollisionWorld;
    };
}