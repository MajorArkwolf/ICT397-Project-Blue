#include "BeBoxBody.hpp"

#include "BeCollisionWorld.hpp"

BeBoxBody::BeBoxBody(glm::vec3 position, glm::quat rotation, glm::vec3 extent,
                     BeCollisionWorld *world, beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform         = rp3d::Transform(pos, rot);
    body              = world->CreateCollisionBody(transform);
    rp3d::Vector3 ext = rp3d::Vector3(extent.x, extent.y, extent.z);
    shape             = new rp3d::BoxShape(ext);
    body->addCollisionShape(shape, transform);
    bodyId = targetId;
}

BeBoxBody::~BeBoxBody() {
    delete shape;
    delete body;
}

rp3d::CollisionBody *BeBoxBody::GetBody() {
    return body;
}

void BeBoxBody::SetTransform(glm::vec3 position, glm::quat rotation) {

    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform *BeBoxBody::GetTransform() {
    BeTransform *result = new BeTransform(body->getTransform());
    return result;
}

beBodyId BeBoxBody::GetId() {
    return bodyId;
}