#include "BeSphereBody.hpp"

#include "BeCollisionWorld.hpp"

BeSphereBody::BeSphereBody(glm::vec3 position, glm::quat rotation, float radius,
                           BeCollisionWorld *world, beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform         = rp3d::Transform(pos, rot);
    body              = world->CreateCollisionBody(transform);
    rp3d::decimal rad = rp3d::decimal(radius);
    shape             = new rp3d::SphereShape(rad);
    body->addCollisionShape(shape, transform);
    bodyId = targetId;
}

BeSphereBody::~BeSphereBody(){
    delete shape;
    delete body;
}

rp3d::CollisionBody *BeSphereBody::GetBody() {
    return body;
}

void BeSphereBody::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform *BeSphereBody::GetTransform() {
    BeTransform *result = new BeTransform(transform);
    return result;
}

beBodyId BeSphereBody::GetId() {
    return bodyId;
}