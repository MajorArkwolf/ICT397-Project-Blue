#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/CollisionBody.hpp"
#include "Controller/PhysicsFacade/React/ReactShapes.hpp"

namespace Physics {

    class ReactCollisionBody : public CollisionBody {
      public:
        ReactCollisionBody(rp3d::CollisionBody *body);

        /**
         *@brief Sets the position of the body
         *@param position The position to set to
         */
        void SetPosition(glm::vec3 position) override;

        /**
         *@brief Sets the orientation of the body
         *@param orientation The orientation to set to
         */
        void SetOrientation(glm::quat orientation) override;

        /**
         *@brief Sets the position and orientation of the body
         *@param orientation The orientation to set to
         * @param position The position to set to
         */
        void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) override;
        /**
         *@brief Gets the position of the body
         */
        glm::vec3 GetPosition() override;

        /**
         *@brief Gets the orientation of the body
         */
        glm::quat GetOrientation() override;

        /**
         *@brief Destroys the body
         */
        void Destroy() override;

        /**
         *@brief Adds the given collision shape to the object at the given position and orientation
         *@param shape The collision shape to add
         *@param position The position to add the shape at
         *@param orientation The orientation to add the shape at
         */
        void AddCollisionShape(ReactCollisionShape shape, glm::vec3 position, glm::quat orientation);

      private:
        friend class ReactCollisionWorld;
        rp3d::CollisionBody *collisionBody = nullptr;
    };
}
