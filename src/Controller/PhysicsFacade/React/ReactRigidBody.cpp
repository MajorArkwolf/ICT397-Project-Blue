#include "ReactRigidBody.hpp"
#include "ReactHelper.hpp"

Physics::ReactRigidBody::ReactRigidBody(rp3d::RigidBody * body) {
    rigidBody = body;
}

Physics::ReactRigidBody::~ReactRigidBody() {}

void Physics::ReactRigidBody::SetPosition(glm::vec3 position) {
    rp3d::Transform currentTransform = rigidBody->getTransform();
    rp3d::Transform newTransform;
    rp3d::Vector3 newPosition = ReactHelper::ConvertVec3(position);

    newTransform.setOrientation(currentTransform.getOrientation());
    newTransform.setPosition(newPosition);


    rigidBody->setTransform(newTransform);
}

void Physics::ReactRigidBody::SetOrientation(glm::quat orientation) {

    rp3d::Transform currentTransform = rigidBody->getTransform();

    rp3d::Transform newTransform;
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);

    newTransform.setOrientation(newOrientation);
    newTransform.setPosition(currentTransform.getPosition());

    rigidBody->setTransform(newTransform);
}

void Physics::ReactRigidBody::SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) {
    rp3d::Vector3 newPosition = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform newTransform(newPosition, newOrientation);
    rigidBody->setTransform(newTransform);
   
}

glm::vec3 Physics::ReactRigidBody::GetPosition() {
    auto transform = this->rigidBody->getTransform();
    auto pos       = transform.getPosition();
    return ReactHelper::ConvertVec3(pos);

}

glm::quat Physics::ReactRigidBody::GetOrientation() {
    auto transform = this->rigidBody->getTransform();
    auto orien     = transform.getOrientation();
    return ReactHelper::ConvertQuaternion(orien);
}

void Physics::ReactRigidBody::SetSleeping(bool sleeping) {
    rigidBody->setIsSleeping(sleeping);
}

bool Physics::ReactRigidBody::GetSleeping() {
    return rigidBody->isSleeping();
}

void Physics::ReactRigidBody::ApplyForceToCentre(glm::vec3 force) {
    rp3d::Vector3 addedForce = ReactHelper::ConvertVec3(force);
    rigidBody->applyForceToCenterOfMass(addedForce);
}

void Physics::ReactRigidBody::ApplyForce(glm::vec3 force, glm::vec3 point) {

    rp3d::Vector3 addedForce = ReactHelper::ConvertVec3(force);
    rp3d::Vector3 pointForce = ReactHelper::ConvertVec3(point);
    rigidBody->applyForce(addedForce, pointForce);
}

void Physics::ReactRigidBody::Destroy() {}

void Physics::ReactRigidBody::AddCollisionShape(ReactCollisionShape shape, glm::vec3 position,
                                                glm::quat orientation, float mass) {
    rp3d::Vector3 newPosition       = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform newTransform(newPosition, newOrientation);
    rigidBody->addCollisionShape(shape.GetShape().get(), newTransform, mass);
}

void Physics::ReactRigidBody::SetBodyType(int type) {
    switch (type) {
        case 0: {
            rigidBody->setType(rp3d::BodyType::KINEMATIC);
        } break;
        case 1: {
            rigidBody->setType(rp3d::BodyType::DYNAMIC);
        } break;
        case 2: {
            rigidBody->setType(rp3d::BodyType::STATIC);
        } break;
        default: break;
    }
}

void Physics::ReactRigidBody::SetMass(float mass) {
    rigidBody->setMass(mass);
}
