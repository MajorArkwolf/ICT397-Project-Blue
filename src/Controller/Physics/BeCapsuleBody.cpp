#include "BeCapsuleBody.hpp"

#include "BeCollisionWorld.hpp"

BeCapsuleBody::BeCapsuleBody(glm::vec3 position, glm::quat rotation,
                             float radius, float height,
                             BeCollisionWorld *world, beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform         = rp3d::Transform(pos, rot);
    body              = world->CreateCollisionBody(transform);
    rp3d::decimal rad = rp3d::decimal(radius);
    rp3d::decimal h   = rp3d::decimal(height);
    shape             = new rp3d::CapsuleShape(rad, h);
    body->addCollisionShape(shape, transform);
    bodyId = targetId;
}

BeCapsuleBody::~BeCapsuleBody() {
    delete shape;
    delete body;
}

rp3d::CollisionBody *BeCapsuleBody::GetBody() {
    return body;
}

void BeCapsuleBody::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform *BeCapsuleBody::GetTransform() {
    BeTransform *result = new BeTransform(transform);
    return result;
}

beBodyId BeCapsuleBody::GetId() {
    return bodyId;
}