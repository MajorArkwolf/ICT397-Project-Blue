#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/DynamicsWorld.hpp"
#include "ReactRigidBody.hpp"

namespace Physics {
    class ReactDynamicsWorld : public DynamicsWorld {
      public:
        ReactDynamicsWorld(glm::vec3 gravity);
        ~ReactDynamicsWorld();
        void InitialiseWorld(glm::vec3 gravity) override;
        void Update(double deltaTime) override;
        RigidBodyID CreateRigidBody(glm::vec3 position, glm::quat) override;

      private:
        std::map<RigidBodyID, ReactRigidBody> rigidBodies;
        rp3d::DynamicsWorld dynamicsWorld;
    };
}
