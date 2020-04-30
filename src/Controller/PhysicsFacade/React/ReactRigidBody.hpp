#pragma once
#include <reactphysics3d.h>

#include "Controller/PhysicsFacade/RigidBody.hpp"
#include  "Controller/PhysicsFacade/React/ReactShapes.hpp"


namespace Physics {

    class ReactRigidBody : public RigidBody {
      public:
        ReactRigidBody(rp3d::RigidBody *body);
        ~ReactRigidBody();
        void SetPosition(glm::vec3 position) override;
        void SetOrientation(glm::quat orientation) override;
        void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) override;
        glm::vec3 GetPosition() override;
        glm::quat GetOrientation() override;
        void SetSleeping(bool sleeping) override;
        bool GetSleeping() override;
        void ApplyForceToCentre(glm::vec3 force) override;
        void ApplyForce(glm::vec3 force, glm::vec3 point) override;
        void Destroy() override;
        void AddCollisionShape(ReactCollisionShape, glm::vec3 position, glm::quat orientation,
                               float mass);
        void SetBodyType(int type);
        void SetMass(float mass);

      private:
        rp3d::RigidBody *rigidBody = nullptr;
    };
}
