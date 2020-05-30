#pragma once
#include <map>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "RigidBody.hpp"

namespace Physics {
    using RigidBodyID = size_t;
    /**
     * @class DynamicsWorld
     * @brief Represents a physics dynamics world, handles access to all associated rigid bodies
     */
    class DynamicsWorld {
      public:
        /// Constructor
        DynamicsWorld(){}
        /// Desttructor
        virtual ~DynamicsWorld(){}
        /**
         * @brief Used to intialise a dynamics world with a certain gravity level
         * @param gravity The gravity of the world
         */
        virtual void InitialiseWorld(glm::vec3 gravity) = 0;

        /**
         * @brief Updates the dynamic world with the given delta time
         * @param deltaTime The amount of time since the last physics update
         */
        virtual void Update(double deltaTime) = 0;

        /**
         * @brief Creates a rigid body in the dyanmics world and returns the id needed to access it
         * @param position The starting position of the rigid body
         * @param rotation The starting rotation of the rigid body
         * @param gameObjectID The id of the object to create
         */
        virtual void CreateRigidBody(glm::vec3 position, glm::quat rotation, size_t gameObjectID) = 0;

        /**
         * @brief Returns a rigid body with the id given
         * @param id The ID of the rigid Body to return
         * @return The Rigid body associated with the given id, nullptr if not found
         */
        virtual RigidBody *GetRigidBody(RigidBodyID id) = 0;
    };
}
