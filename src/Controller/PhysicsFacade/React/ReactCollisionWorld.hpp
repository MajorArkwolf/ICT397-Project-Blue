#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/CollisionWorld.hpp"
#include "ReactCollisionBody.hpp"

namespace Physics {
    class ReactCollisionWorld : public CollisionWorld {
      public:
        ReactCollisionWorld();
        ~ReactCollisionWorld();
        void InitialiseWorld() override;
        void CreateCollisionBody(glm::vec3 position, glm::quat orientation, size_t gameObjectID) override;
        CollisionBody *GetCollisionBody(CollisionBodyID bodyID) override;
        bool TestOverlap(CollisionBodyID first, CollisionBodyID seconds) override;
        bool TestAABBOverlap(CollisionBodyID first, CollisionBodyID second) override;

      private:
        std::map<size_t, ReactCollisionBody> collisionBodies;
        rp3d::CollisionWorld collisionWorld;
    };
}
