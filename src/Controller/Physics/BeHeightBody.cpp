#include "BeHeightBody.hpp"

#include "BeCollisionWorld.hpp"

BeHeightBody::BeHeightBody(glm::vec3 position, glm::quat rotation, int width,
                           int height, BeCollisionWorld *world, float *terrain,
                           beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    rp3d::Transform transform = rp3d::Transform(pos, rot);
    body                      = world->CreateCollisionBody(transform);
    rp3d::Vector3 extent      = rp3d::Vector3(1, 1, 1);
    shape                     = new rp3d::HeightFieldShape(
        width, height, 0, 255, terrain,
        rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
    body->addCollisionShape(shape, transform);
    bodyId = targetId;
}

rp3d::CollisionBody *BeHeightBody::GetBody() {
    return body;
}

void BeHeightBody::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
}

BeTransform *BeHeightBody::GetTransform() {
    BeTransform *result = new BeTransform(transform);
    return result;
}

beBodyId BeHeightBody::GetId() {
    return bodyId;
}