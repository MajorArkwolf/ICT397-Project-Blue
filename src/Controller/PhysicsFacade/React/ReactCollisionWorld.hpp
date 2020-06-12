#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/CollisionWorld.hpp"
#include "ReactCollisionBody.hpp"

namespace Physics {
    class ReactCollisionWorld : public CollisionWorld {
      public:
        ReactCollisionWorld();
        ~ReactCollisionWorld();

        /**
         *@brief Initialises the Colision world
         */
        void InitialiseWorld() override;

        /**
         *@brief Creates a collision body at the specified position, orientation and with the specified id
         *@param position The position
         *@param orientation The orientation
         *@param gameObjectID The id store that object at in the map
         */
        void CreateCollisionBody(glm::vec3 position, glm::quat orientation, size_t gameObjectID) override;

        /**
         *@brief Gets the collision body at the specified id key in the map
         */
        CollisionBody *GetCollisionBody(CollisionBodyID bodyID) override;

        /**
         *@brief Tests overlap beetween the first and second bodies, checks for overlap between the collision shapes added to them
         *@param first The first body id
         *@param seconds The second body id
         */
        bool TestOverlap(CollisionBodyID first, CollisionBodyID seconds) override;

        /**
         *@brief Tests AABB overlap beetween the first and second bodies, makes an AABB box for each
         *object that encompasses all their shapes and checks for overlap
         *@param first The first body id
         *@param second The second body id
         */
        bool TestAABBOverlap(CollisionBodyID first, CollisionBodyID second) override;
        void DestroyBody(CollisionBodyID id);

      private:
        std::map<size_t, ReactCollisionBody> collisionBodies;
        rp3d::CollisionWorld collisionWorld;
    };
}
