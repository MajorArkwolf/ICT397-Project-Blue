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
    dynamicsWorld.update(static_cast<float>(deltaTime));
}

void Physics::ReactDynamicsWorld::CreateRigidBody(glm::vec3 position, glm::quat orientation, size_t gameObjectID) {
    rp3d::Vector3 bodyPosition = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion bodyOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform transform(bodyPosition, bodyOrientation);
    rp3d::RigidBody *body;

    //Creates a react rigid body in this dynamics world
    body = dynamicsWorld.createRigidBody(transform);


    ReactRigidBody reactRigidBody = ReactRigidBody(body);

    //Adds the rigid body to the map of rigid bodies
    rigidBodies.insert(std::make_pair(gameObjectID, reactRigidBody));
    
}

Physics::RigidBody* Physics::ReactDynamicsWorld::GetRigidBody(RigidBodyID bodyID) {
    return &rigidBodies.at(bodyID);
}
