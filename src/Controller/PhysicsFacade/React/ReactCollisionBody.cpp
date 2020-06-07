#include "ReactCollisionBody.hpp"
#include "ReactHelper.hpp"

Physics::ReactCollisionBody::ReactCollisionBody(rp3d::CollisionBody * body) {
    collisionBody = body;
}

void Physics::ReactCollisionBody::SetPosition(glm::vec3 position) {
    rp3d::Transform currentTransform = collisionBody->getTransform();
    rp3d::Transform newTransform;
    rp3d::Vector3 newPosition = ReactHelper::ConvertVec3(position);

    newTransform.setOrientation(currentTransform.getOrientation());
    newTransform.setPosition(newPosition);


    collisionBody->setTransform(newTransform);
}

void Physics::ReactCollisionBody::SetOrientation(glm::quat orientation) {

    rp3d::Transform currentTransform = collisionBody->getTransform();

    rp3d::Transform newTransform;
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);

    newTransform.setOrientation(newOrientation);
    newTransform.setPosition(currentTransform.getPosition());

    collisionBody->setTransform(newTransform);
}

void Physics::ReactCollisionBody::SetPositionAndOrientation(glm::vec3 position, glm::quat orientation) {
    rp3d::Vector3 newPosition = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform newTransform(newPosition, newOrientation);
    collisionBody->setTransform(newTransform);
   
}

glm::vec3 Physics::ReactCollisionBody::GetPosition() {
    auto transform = this->collisionBody->getTransform();
    auto pos       = transform.getPosition();
    return ReactHelper::ConvertVec3(pos);

}

glm::quat Physics::ReactCollisionBody::GetOrientation() {
    auto transform = this->collisionBody->getTransform();
    auto orien     = transform.getOrientation();
    return ReactHelper::ConvertQuaternion(orien);
}

void Physics::ReactCollisionBody::Destroy() {}

void Physics::ReactCollisionBody::AddCollisionShape(ReactCollisionShape shape, glm::vec3 position,
                                                glm::quat orientation) {
    rp3d::Vector3 newPosition       = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform newTransform(newPosition, newOrientation);
    collisionBody->addCollisionShape(shape.GetShape().get(), newTransform);
}

