#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

namespace Physics {

    enum class RigidBodyType { Static, Kinematic, Dynamic };

    /** 
    * @class RigidBody
    * A pure virtual class that represents a RigidBody for use within a dynamics world
    */
    class RigidBody {
      public:
        RigidBody(){};
        virtual ~RigidBody(){};
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
         * @brief Sets wheter physics should be updated on this body
         * @param sleeping Set to true if the body should not be updated
         */
        virtual void SetSleeping(bool sleeping)                                           = 0;
        /**
         * @brief Returns whether the body is currently not being udpated
         * @return Whether the body is sleeping
         */
        virtual bool GetSleeping()                                                        = 0;
        /**
         * @brief Applies a give force to the centre of the object
         * @param force The amount of force and direction to apply
         */
        virtual void ApplyForceToCentre(glm::vec3 force)                                  = 0;
        /**
         * @brief Applies force to a given point of the body
         * @param force The amount of force to apply
         * @param point The point to apply the force
         */
        virtual void ApplyForce(glm::vec3 force, glm::vec3 point)                         = 0;
        /**
         * @brief Destroys the rigid body when no longer needed
         */
        virtual void Destroy()                                                            = 0;

      private:
      
    };
}
