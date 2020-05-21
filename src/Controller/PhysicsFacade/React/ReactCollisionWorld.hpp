#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/CollisionWorld.hpp"
#include "ReactCollisionBody.hpp"

namespace Physics {
    class ReactCollisionWorld : public CollisionWorld {
      public:
        ReactCollisionWorld(glm::vec3 gravity);
        ~ReactCollisionWorld();
        void InitialiseWorld() override;
        CollisionBodyID CreateCollisionBody(glm::vec3 position, glm::quat) override;
        CollisionBody* GetCollisionBody(CollisionBodyID bodyID) override;

      private:
        std::map<size_t, ReactCollisionBody> rigidBodies;
        rp3d::CollisionWorld collisionWorld;
    };
}
