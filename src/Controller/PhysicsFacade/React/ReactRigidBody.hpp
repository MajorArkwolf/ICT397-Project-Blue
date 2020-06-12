#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/React/ReactShapes.hpp"
#include "Controller/PhysicsFacade/RigidBody.hpp"

namespace Physics {

    /**
     *@class ReactRigidBody
     *@brief A wrapper for the React RigidBody class, inherits from RigidBody derived object
     */
    class ReactRigidBody : public RigidBody {

      public:
        enum class RigidBodyType { STATIC, DYNAMIC, KINEMATIC };

        /**
         *@brief The sole constructor that takes in a react rigid body pointer
         *@param body The rp3d rigid body pointer
         */
        ReactRigidBody(rp3d::RigidBody *body);
        ~ReactRigidBody();
        /**
         *@brief Sets the position of the rigid body
         *@param position The position to set the rigid body to
         */
        void SetPosition(glm::vec3 position) override;
        /**
         *@brief Sets the orientation of the rigid body
         *@param orientation The quaternion orientation to set to
         */
        void SetOrientation(glm::quat orientation) override;
        /**
         *@brief Sets both the position and the orientation at the same time
         *@param position The position to set to
         *@param orientation The orientation to set to
         */
        void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) override;

        /**
         *@brief Gets the position of the rigid body
         */
        glm::vec3 GetPosition() override;
        /**
         *@brief Gets the orientation of the rigid body
         */
        glm::quat GetOrientation() override;

        /**
         *@brief Sets whether the dynamic body should be sleeping
         *@param sleeping Sleeping or not
         */
        void SetSleeping(bool sleeping) override;
        /**
         *@brief Gets whether the rigid body is sleeping
         */
        bool GetSleeping() override;
        /**
         *@brief Applies the given force to the centre of the rigid body
         *@param force The force to apply to the centre
         */
        void ApplyForceToCentre(glm::vec3 force) override;

        /**
         *@brief Applies the given force to the given point
         *@param force The force to add to the object
         *@param point The point to add the force
         */
        void ApplyForce(glm::vec3 force, glm::vec3 point) override;

        /**
         *@brief Destroys the rigid body
         */
        void Destroy() override;

                /**
         *@brief Adds the given collision shape to the rigid body
         *@param shape The shape to add to the body
         *@param position The position to set the shape at
         *@param orientation The orientation of the shape
         *@param mass The mass of the shape
         */
        void AddCollisionShape(ReactCollisionShape shape, glm::vec3 position, glm::quat orientation,
                               float mass);

                /**
         *@brief Sets the type of the collision body
         *@param type The type of the rigid body
         */
        void SetBodyType(RigidBodyType type);

                /**
         *@brief Sets the mass of the rigid body
         *@param mass The mass to set the rigid body to
         */
        void SetMass(float mass);

                /**
         *@brief Sets the angular damping of the rigid body
         *@param damping A value between 0 and 1
         */
        void SetAngularDamping(double damping) override;
        /**
         *@brief Sets the bounciness of the object
         *@param bounciness A value between 0 and 1
         */
        void SetBounciness(float bounciness);

        void SetFrictionCoefficient(float friction);
        void SetRollingResistance(float resistance);

      private:
        rp3d::RigidBody *rigidBody = nullptr;
    };
}
