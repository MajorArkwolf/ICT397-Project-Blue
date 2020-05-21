#include "ReactCollisionWorld.hpp"

#include "ReactHelper.hpp"

Physics::ReactCollisionWorld::ReactCollisionWorld(glm::vec3 gravity) {}

Physics::ReactCollisionWorld::~ReactCollisionWorld() {}

void Physics::ReactCollisionWorld::InitialiseWorld() {}

Physics::CollisionBodyID Physics::ReactCollisionWorld::CreateCollisionBody(glm::vec3 position,
                                                                           glm::quat orientation) {
    static CollisionBodyID collisionBodyCount = 0;
    rp3d::Vector3 bodyPosition                = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion bodyOrientation          = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform transform(bodyPosition, bodyOrientation);
    rp3d::CollisionBody *body;

    // Creates a react rigid body in this dynamics world
    body = collisionWorld.createCollisionBody(transform);

    ReactCollisionBody reactCollisionBody = ReactCollisionBody(body);
    collisionBodyCount++;

    // Adds the rigid body to the map of rigid bodies
    rigidBodies.insert(std::make_pair(collisionBodyCount, reactCollisionBody));

    // Returns the key to the rigid body
    return collisionBodyCount;
}

Physics::CollisionBody *Physics::ReactCollisionWorld::GetCollisionBody(CollisionBodyID bodyID) {
    return &rigidBodies.at(bodyID);
}
