#include "ReactRigidBody.hpp"
#include "ReactHelper.hpp"

Physics::ReactRigidBody::ReactRigidBody(rp3d::RigidBody * body) {
    rigidBody = body;
}

Physics::ReactRigidBody::~ReactRigidBody() {
    for (size_t i = 0; i < rigidBody->getNbColliders(); ++i) {
        rigidBody->removeCollider(rigidBody->getCollider(i));
    }
}

void Physics::ReactRigidBody::SetPosition(glm::vec3 position) {
    rp3d::Transform currentTransform = rigidBody->getTransform();
    rp3d::Transform newTransform;
    rp3d::Vector3 newPosition = ReactHelper::ConvertVec3(position);

    newTransform.setOrientation(currentTransform.getOrientation());
    newTransform.setPosition(newPosition);


    rigidBody->setTransform(newTransform);
}

void Physics::ReactRigidBody::SetOrientation(glm::quat orientation) {

    const rp3d::Transform currentTransform = rigidBody->getTransform();

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
    rigidBody->setIsAllowedToSleep(sleeping);
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
    rigidBody->applyForceAtLocalPosition(addedForce, pointForce);
}

void Physics::ReactRigidBody::Destroy() {}

void Physics::ReactRigidBody::AddCollisionShape(ReactCollisionShape shape, glm::vec3 position,
                                                glm::quat orientation, float mass) {
    rp3d::Vector3 newPosition       = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion newOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform newTransform(newPosition, newOrientation);
    auto collider = rigidBody->addCollider(shape.GetShape().get(), newTransform);
    auto& mat = collider->getMaterial();
    mat.setMassDensity(mass);
    //rigidBody->addCollisionShape(shape.GetShape().get(), newTransform, mass);
}

void Physics::ReactRigidBody::SetBodyType(RigidBodyType type) {
    switch (type) {
        case RigidBodyType::KINEMATIC: {
            rigidBody->setType(rp3d::BodyType::KINEMATIC);
        } break;
        case RigidBodyType::DYNAMIC: {
            rigidBody->setType(rp3d::BodyType::DYNAMIC);
        } break;
        case RigidBodyType::STATIC: {
            rigidBody->setType(rp3d::BodyType::STATIC);
        } break;
    }
}

void Physics::ReactRigidBody::SetMass(float mass) {
    rigidBody->setMass(mass);
}

void Physics::ReactRigidBody::SetAngularDamping(double damping) {
    rigidBody->setAngularDamping(damping);
}

void Physics::ReactRigidBody::SetBounciness(float bounciness) {
    auto collider = rigidBody->getCollider(0);
    auto &mat = collider->getMaterial();
    mat.setBounciness(bounciness);
}

void Physics::ReactRigidBody::SetFrictionCoefficient(float friction) {
    auto collider = rigidBody->getCollider(0);
    auto &mat = collider->getMaterial();
    mat.setFrictionCoefficient(friction);
}

void Physics::ReactRigidBody::SetRollingResistance(float resistance) {
    auto collider = rigidBody->getCollider(0);
    auto &mat = collider->getMaterial();
    mat.setRollingResistance(resistance);
}

