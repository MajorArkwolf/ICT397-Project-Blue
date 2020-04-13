#pragma once
#include <map>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "RigidBody.hpp"

namespace Physics {
    using RigidBodyID = size_t;
    class DynamicsWorld {
      public:
        DynamicsWorld(){};
        virtual ~DynamicsWorld(){};
        virtual void InitialiseWorld(glm::vec3 gravity)                          = 0;
        virtual void Update(double deltaTime)                                    = 0;
        virtual RigidBodyID CreateRigidBody(glm::vec3 position, glm::quat) = 0;

    };
}
