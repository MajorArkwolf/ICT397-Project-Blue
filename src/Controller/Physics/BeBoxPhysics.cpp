#include "BeBoxPhysics.hpp"

#include "BeDynamicWorld.hpp"

BeBoxPhysics::BeBoxPhysics(glm::vec3 position, glm::quat rotation, glm::vec3 extent, beScalar mass,
                           BeDynamicWorld *world, beBodyId targetId) {

    rp3d::Vector3 pos    = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform            = rp3d::Transform(pos, rot);
    body                 = world->CreateRigidBody(transform);
    rp3d::Vector3 ext    = rp3d::Vector3(extent.x, extent.y, extent.z);
    shape                = new rp3d::BoxShape(ext);
    body->addCollisionShape(shape, transform, mass);
    bodyId = targetId;

}
BeBoxPhysics::~BeBoxPhysics() {

    delete shape;
}

rp3d::RigidBody *BeBoxPhysics::GetBody() {
    return body;
}

void BeBoxPhysics::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos    = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform            = rp3d::Transform(pos, rot);
    body->setTransform(transform);

}

BeTransform BeBoxPhysics::GetTransform() {
    BeTransform result(body->getTransform());
    return result;
}

beBodyId BeBoxPhysics::GetId() {
    return bodyId;
}

void BeBoxPhysics::EnableGravity(bool gravity) {
    body->enableGravity(gravity);
}

void BeBoxPhysics::SetType(BeBodyType type) {
    body->setType(type);
}

BeMaterial BeBoxPhysics::GetMaterial() {
    BeMaterial result(body->getMaterial());
    return result;
}

bool BeBoxPhysics::IsSleepEnabled() {
    return body->isAllowedToSleep();
}

void BeBoxPhysics::SetSleep(bool toggle) {
    body->setIsAllowedToSleep(toggle);
}