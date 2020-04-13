#include "ReactDynamicsWorld.hpp"

#include "ReactHelper.hpp"

Physics::ReactDynamicsWorld::ReactDynamicsWorld(glm::vec3 gravity)
    : dynamicsWorld(ReactHelper::ConvertVec3(gravity)) {}

Physics::ReactDynamicsWorld::~ReactDynamicsWorld() {}

void Physics::ReactDynamicsWorld::InitialiseWorld(glm::vec3 gravity) {
    auto dgravity = ReactHelper::ConvertVec3(gravity);
    dynamicsWorld.setGravity(dgravity);
}

void Physics::ReactDynamicsWorld::Update(double deltaTime) {
    dynamicsWorld.update(deltaTime);
}

Physics::RigidBodyID Physics::ReactDynamicsWorld::CreateRigidBody(glm::vec3 position, glm::quat orientation) {
    static RigidBodyID rigidBodyCount            = 0;
    rp3d::Vector3 bodyPosition = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion bodyOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform transform(bodyPosition, bodyOrientation);
    rp3d::RigidBody *body;
    body = dynamicsWorld.createRigidBody(transform);


    ReactRigidBody reactRigidBody = ReactRigidBody(body);
    rigidBodyCount++;
    rigidBodies.insert(std::make_pair(rigidBodyCount, reactRigidBody));
    return rigidBodyCount;
    
}
