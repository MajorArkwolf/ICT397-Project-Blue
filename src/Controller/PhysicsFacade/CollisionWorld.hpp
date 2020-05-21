#pragma once
#include <map>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "CollisionBody.hpp"

namespace Physics {
    using CollisionBodyID = size_t;
    /**
     * @class DynamicsWorld
     * @brief Represents a physics dynamics world, handles access to all associated rigid bodies
     */
    class CollisionWorld {
      public:
        /// Constructor
        CollisionWorld(){};
        /// Desttructor
        virtual ~CollisionWorld(){};
        /**
         * @brief Used to intialise a dynamics world with a certain gravity level
         */
        virtual void InitialiseWorld() = 0;

        /**
         * @brief Creates a rigid body in the dyanmics world and returns the id needed to access it
         * @param position The starting position of the rigid body
         * @param rotation The starting rotation of the rigid body
         * @return The ID of the created rigid body
         */
        virtual CollisionBodyID CreateCollisionBody(glm::vec3 position, glm::quat rotation) = 0;

        /**
         * @brief Returns a rigid body with the id given
         * @param id The ID of the rigid Body to return
         * @return The Rigid body associated with the given id, nullptr if not found
         */
        virtual CollisionBody *GetCollisionBody(CollisionBodyID id) = 0;

        virtual bool TestCollision(CollisionBodyID first, CollisionBodyID second)   = 0;
        virtual bool TestOverlap(CollisionBodyID first, CollisionBodyID seconds)    = 0;
        virtual bool TestAABBOverlap(CollisionBodyID first, CollisionBodyID second) = 0;
        virtual bool TestPointInside(glm::dvec3 point, CollisionBodyID bodyID)      = 0;
    };
}
