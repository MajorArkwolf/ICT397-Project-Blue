#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

namespace Physics {

    /** 
    * @class RigidBody
    * A pure virtual class that represents a RigidBody for use within a dynamics world
    */
    class CollisionBody {
      public:
        CollisionBody(){}
        virtual ~CollisionBody(){}
        /**
         * @brief Sets the position of the rigid body
         * @param position THe position to set the rigid body to
         */
        virtual void SetPosition(glm::vec3 position)                                      = 0;
        /**
         * @brief Sets the rotation or orientation of the rigid body
         * @param orientation The orietnation to set the rigid body to
         */
        virtual void SetOrientation(glm::quat orientation)                                = 0;
        /**
         * @brief Sets the position and rotation of the rigid body
         * @param position The new position
         * @param orientation The new Orientation
         */
        virtual void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) = 0;
        /**
         * @brief Returns the position of the rigid body within the dynamics world
         * @return The position of the rigid body
         */
        virtual glm::vec3 GetPosition()                                                   = 0;
        /**
         * @brief Returns the orientatino of the body relative to the dynamics world
         * @return The orientation of the body
         */
        virtual glm::quat GetOrientation()                                                = 0;
        /**
         * @brief Destroys the rigid body when no longer needed
         */
        virtual void Destroy()                                                            = 0;
      
    };
}
