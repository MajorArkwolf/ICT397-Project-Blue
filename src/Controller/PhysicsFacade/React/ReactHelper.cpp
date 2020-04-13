#include "ReactHelper.hpp"

glm::quat Physics::ReactHelper::ConvertQuaternion(rp3d::Quaternion quat) {
    glm::quat conversion{};
    conversion.x = quat.x;
    conversion.y = quat.y;
    conversion.z = quat.z;
    conversion.w = quat.w;
    return conversion;
}

rp3d::Quaternion Physics::ReactHelper::ConvertQuaternion(glm::quat quat) {
    rp3d::Quaternion conversion{};
    conversion.x = quat.x;
    conversion.y = quat.y;
    conversion.z = quat.z;
    conversion.w = quat.w;
    return conversion;
}

glm::vec3 Physics::ReactHelper::ConvertVec3(rp3d::Vector3 vec) {
    glm::vec3 conversion{};
    conversion.x = vec.x;
    conversion.y = vec.y;
    conversion.z = vec.z;
    return conversion;
}

rp3d::Vector3 Physics::ReactHelper::ConvertVec3(glm::vec3 vec) {
    rp3d::Vector3 conversion{};
    conversion.x = vec.x;
    conversion.y = vec.y;
    conversion.z = vec.z;
    return conversion;
}
