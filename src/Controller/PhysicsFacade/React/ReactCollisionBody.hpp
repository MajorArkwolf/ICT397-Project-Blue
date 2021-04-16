#pragma once
#include <reactphysics3d/reactphysics3d.h>

#include "Controller/PhysicsFacade/CollisionBody.hpp"
#include "Controller/PhysicsFacade/React/ReactShapes.hpp"

namespace Physics {

    class ReactCollisionBody : public CollisionBody {
      public:
        ReactCollisionBody(rp3d::CollisionBody *body);
        ~ReactCollisionBody() override;
        void SetPosition(glm::vec3 position) override;
        void SetOrientation(glm::quat orientation) override;
        void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) override;
        glm::vec3 GetPosition() override;
        glm::quat GetOrientation() override;
        void Destroy() override;
        void AddCollisionShape(ReactCollisionShape shape, glm::vec3 position, glm::quat orientation);


      private:
        friend class ReactCollisionWorld;
        rp3d::CollisionBody *collisionBody = nullptr;
    };
}
