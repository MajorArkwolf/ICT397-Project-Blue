#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <reactphysics3d/reactphysics3d.h>

namespace Physics {
    /**
     * @class ReactHelper
     * Used to convert between glm and react data types
     */
    class ReactHelper {
      public:
        /**
         * Converts a react quaternion to glm quaternion
         * @param quat The react quaternion to convert
         * @return the GLM quaternion returned
         */
        static glm::quat ConvertQuaternion(rp3d::Quaternion& quat);
        /**
         * Converts a glm quaternion to react quaternion
         * @param quat The glm quaternion to convert
         * @return the react quaternion returned
         */
        static rp3d::Quaternion ConvertQuaternion(glm::quat& quat);
        /**
         * Converts a react vector to glm vector
         * @param vec The react vector to convert
         * @return the GLM vector returned
         */
        static glm::vec3 ConvertVec3(rp3d::Vector3& vec);
        /**
         * Converts a glm vector to react vector
         * @param vec The glm vector to convert
         * @return the react vector returned
         */
        static rp3d::Vector3 ConvertVec3(glm::vec3& vec);

    };
}
