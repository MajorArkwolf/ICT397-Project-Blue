#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <reactphysics3d.h>

namespace Physics {
    class ReactHelper {
      public:
        static glm::quat ConvertQuaternion(rp3d::Quaternion quat);
        static rp3d::Quaternion ConvertQuaternion(glm::quat quat);
        static glm::vec3 ConvertVec3(rp3d::Vector3 vec);
        static rp3d::Vector3 ConvertVec3(glm::vec3 vec);

    };
}
