#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

namespace Physics {

    enum class RigidBodyType { Static, Kinematic, Dynamic };

    class RigidBody {
      public:
        RigidBody(){};
        virtual ~RigidBody(){};
        virtual void SetPosition(glm::vec3 position)                                      = 0;
        virtual void SetOrientation(glm::quat orientation)                                = 0;
        virtual void SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) = 0;
        virtual glm::vec3 GetPosition()                                                   = 0;
        virtual glm::quat GetOrientation()                                                = 0;
        virtual void SetSleeping(bool sleeping)                                           = 0;
        virtual bool GetSleeping()                                                        = 0;
        virtual void ApplyForceToCentre(glm::vec3 force)                                  = 0;
        virtual void ApplyForce(glm::vec3 force, glm::vec3 point)                         = 0;
        virtual void Destroy()                                                            = 0;

      private:
      
    };
}
