#include "BeCapsulePhysics.hpp"
#include "BeDynamicWorld.hpp"

BeCapsulePhysics::BeCapsulePhysics(glm::vec3 position, glm::quat rotation, float mass,
                             float radius, float height,
                             BeDynamicWorld *world, beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform         = rp3d::Transform(pos, rot);
    body              = world->CreateRigidBody(transform);
    rp3d::decimal rad = rp3d::decimal(radius);
    rp3d::decimal h   = rp3d::decimal(height);
    shape             = new rp3d::CapsuleShape(rad, h);
    body->addCollisionShape(shape, transform, mass);
    bodyId = targetId;
}

BeCapsulePhysics::~BeCapsulePhysics(){
    delete shape;
    delete body;
}

rp3d::RigidBody *BeCapsulePhysics::GetBody() {
    return body;
}

void BeCapsulePhysics::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform BeCapsulePhysics::GetTransform() {
    BeTransform result(transform);
    return result;
}

beBodyId BeCapsulePhysics::GetId() {
    return bodyId;
}

void BeCapsulePhysics::EnableGravity(bool gravity) {
    body->enableGravity(gravity);
}

void BeCapsulePhysics::SetType(BeBodyType type) {
    body->setType(type);
}