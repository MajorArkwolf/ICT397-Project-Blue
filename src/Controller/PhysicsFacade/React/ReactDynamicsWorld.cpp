#include "ReactDynamicsWorld.hpp"

#include "ReactHelper.hpp"

Physics::ReactDynamicsWorld::ReactDynamicsWorld(glm::vec3 gravity)
    : dynamicsWorld(ReactHelper::ConvertVec3(gravity)) {}


void Physics::ReactDynamicsWorld::InitialiseWorld(glm::vec3 gravity) {
    auto dgravity = ReactHelper::ConvertVec3(gravity);
    dynamicsWorld.setGravity(dgravity);
}

void Physics::ReactDynamicsWorld::Update(double deltaTime) {
    dynamicsWorld.update(static_cast<float>(deltaTime));
}

void Physics::ReactDynamicsWorld::CreateRigidBody(glm::vec3 position, glm::quat orientation, size_t gameObjectID) {
    rp3d::Vector3 bodyPosition = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion bodyOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform transform(bodyPosition, bodyOrientation);

    //Creates a react rigid body in this dynamics world
    rp3d::RigidBody *body = dynamicsWorld.createRigidBody(transform);

    //Adds the rigid body to the map of rigid bodies
    rigidBodies.emplace(std::make_pair(gameObjectID, ReactRigidBody(body)));
    
}

Physics::RigidBody* Physics::ReactDynamicsWorld::GetRigidBody(RigidBodyID bodyID) {
    return &rigidBodies.at(bodyID);
}

void Physics::ReactDynamicsWorld::DestroyBody(RigidBodyID id) {
    rigidBodies.at(id).Destroy();
    rigidBodies.erase(id);

}
