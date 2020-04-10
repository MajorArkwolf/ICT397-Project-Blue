#include "BeSpherePhysics.hpp"
#include "BeDynamicWorld.hpp"

BeSpherePhysics::BeSpherePhysics(glm::vec3 position, glm::quat rotation, float mass, float radius,
                           BeDynamicWorld *world, beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform         = rp3d::Transform(pos, rot);
    body              = world->CreateRigidBody(transform);
    rp3d::decimal rad = rp3d::decimal(radius);
    shape             = new rp3d::SphereShape(rad);
    body->addCollisionShape(shape, transform, mass);
    bodyId = targetId;
}

rp3d::RigidBody *BeSpherePhysics::GetBody() {
    return body;
}

void BeSpherePhysics::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform *BeSpherePhysics::GetTransform() {
    BeTransform *result = new BeTransform(transform);
    return result;
}

beBodyId BeSpherePhysics::GetId() {
    return bodyId;
}