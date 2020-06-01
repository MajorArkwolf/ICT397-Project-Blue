#pragma once


#include "Controller/PhysicsFacade/React/ReactCollisionWorld.hpp"
#include "Controller/PhysicsFacade/React/ReactDynamicsWorld.hpp"
#include "Controller/PhysicsFacade/React/ReactShapes.hpp"
#include "Controller/Engine/LuaManager.hpp"

namespace Physics {
    /**
     *@class PhysicsManager
     *@brief A class the manages a 
     */
    class PhysicsManager {
        enum class PhysicsLibrary { REACT };

      public:
        /**
         *@brief Gets the Physics manager singleton
         *@return the Physics Manager singleton
         */
        static auto GetInstance() -> PhysicsManager &;

        /**
         *@brief Gets the dynamics world object currently no support for multiple different dynamics worlds at the same time
         * @return A pointer to the dynamics world currently initialised
         */
        DynamicsWorld *GetDynamicsWorld();

        /**
         *@brief Gets the collision world object currently no support for multiple different collision worlds at the same time
         * @return A pointer to the dynamics world currently initialised
         */
        CollisionWorld *GetCollisionWorld();

        ShapeFactory *GetShapeFactory();

        ReactShapes *GetReactShapeFactory();
        /**
         *@brief Initialises the collision world using the specified library type
         *@param type The type of physics library to use
         */
        void InitialiseCollisionWorld(PhysicsLibrary type = PhysicsLibrary::REACT);

        /**
         *@brief Initialises the dynamics world using the specified library type
         *@param type the type of physics library to use
         *@param gravity The gravity to set in the dynamics world
         *
         */
        void InitialiseDynamicsWorld(PhysicsLibrary type = PhysicsLibrary::REACT,
                                     glm::vec3 gravity   = glm::vec3(0, -9.8f, 0));

        void InitialiseShapeFactory(PhysicsLibrary type = PhysicsLibrary::REACT);

        void UpdateDynamicsWorld(double deltaTime);
      private:

        static void lua_initialiseReact();
        static CollisionWorld* lua_getCollisionWorld();
        static DynamicsWorld* lua_getDynamicsWorld();
        static ReactCollisionWorld *lua_getReactCollisionWorld();
        static ReactDynamicsWorld *lua_getReactDynamicsWorld();
        void LuaInit();
        static ReactRigidBody *getReactRigid(RigidBody* ptr);

        PhysicsManager();

        /// Dynamics world pointer
        std::unique_ptr<DynamicsWorld> dynamicsWorld;

        ///Collision world pointer
        std::unique_ptr<CollisionWorld> collisionWorld;

        ///Shape factory pointer
        std::unique_ptr<ShapeFactory> shapeFactory;
    };
}
