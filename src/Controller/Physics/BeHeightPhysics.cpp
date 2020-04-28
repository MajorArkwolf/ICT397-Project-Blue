#include "BeHeightPhysics.hpp"
#include "BeDynamicWorld.hpp"

BeHeightPhysics::BeHeightPhysics(glm::vec3 position, glm::quat rotation, float mass, int width,
                           int height, BeDynamicWorld *world, float *terrain,
                           beBodyId targetId) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    rp3d::Transform transform = rp3d::Transform(pos, rot);
    body                      = world->CreateRigidBody(transform);
    rp3d::Vector3 extent      = rp3d::Vector3(1, 1, 1);
    shape                     = new rp3d::HeightFieldShape(
        width, height, 0, 255, terrain,
        rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
    body->addCollisionShape(shape, transform, mass);
    bodyId = targetId;
}

BeHeightPhysics::~BeHeightPhysics(){
    delete shape;
}

rp3d::RigidBody *BeHeightPhysics::GetBody() {
    return body;
}

void BeHeightPhysics::SetTransform(glm::vec3 position, glm::quat rotation) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot =
        rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
    transform = rp3d::Transform(pos, rot);
    body->setTransform(transform);
}

BeTransform BeHeightPhysics::GetTransform() {
    BeTransform result(body->getTransform());
    return result;
}

beBodyId BeHeightPhysics::GetId() {
    return bodyId;
}

void BeHeightPhysics::EnableGravity(bool gravity) {
    body->enableGravity(gravity);
}

void BeHeightPhysics::SetType(BeBodyType type) {
    body->setType(type);
}

BeMaterial &BeHeightPhysics::GetMaterial() {
    BeMaterial result(body->getMaterial());
    return result;
}

bool BeHeightPhysics::IsSleepEnabled() {
    return body->isAllowedToSleep();
}

void BeHeightPhysics::SetSleep(bool toggle) {
    body->setIsAllowedToSleep(toggle);
}

void BeHeightPhysics::ApplyForceToCentre(const glm::vec3 &force) {
    rp3d::Vector3 f(force.x, force.y, force.z);
    body->applyForceToCenterOfMass(f);
}

glm::vec3 BeHeightPhysics::GetVertexAt(int inputX, int inputY) {
    rp3d::Vector3 temp = shape->getVertexAt(inputX, inputY);
    glm::vec3 result(temp.x, temp.y, temp.z);
    return result;
}