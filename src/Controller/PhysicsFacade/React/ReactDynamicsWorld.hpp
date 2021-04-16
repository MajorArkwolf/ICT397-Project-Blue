#pragma once
#include <reactphysics3d/reactphysics3d.h>

#include "Controller/PhysicsFacade/DynamicsWorld.hpp"
#include "ReactRigidBody.hpp"

namespace Physics {

    /**
     *@class ReactDynamicsWorld
     *@param An facade of the react dynamic world class
     */
    class ReactDynamicsWorld : public DynamicsWorld {
      public:
        /**
         *@brief Creates a new collision world with the given gravity
         *@param gravity The gravity to set the world to
         */
        ReactDynamicsWorld(glm::vec3 gravity);

        ~ReactDynamicsWorld() override;

        /**
         *@brief Initialises the world with the given gravity
         *@param gravity The gravity to set the world to
         */
        void InitialiseWorld(glm::vec3 gravity) override;
        /**
         *@brief Updates the dynamic world so that it can simulate physics
         *@param deltaTime The amount of time since the last physics update in seconds
         */
        void Update(double deltaTime) override;

        /**
         *@brief Creates a new rigid body in the world with the given position , orientation and ID
         *@param position The position of the rigidbody
         *@param orientation The orientation of the rigidbody
         *@param gameObjectID The ID of the rigid body to be used for retrieval later
         */
        void CreateRigidBody(glm::vec3 position, glm::quat orientation, size_t gameObjectID) override;

        /**
         *@brief Gets a rigid body with the given ID
         *@param bodyID The ID of the body to return
         *@return The rigid body contained at the given id
         */
        RigidBody *GetRigidBody(RigidBodyID bodyID) override;

        /**
         *@brief Destroyes the rigid body and removes it from react and the map of rigidbodies
         */
        void DestroyBody(RigidBodyID id);

      private:
        std::map<size_t, ReactRigidBody> rigidBodies;
        reactphysics3d::PhysicsWorld* dynamicsWorld;
    };
}
