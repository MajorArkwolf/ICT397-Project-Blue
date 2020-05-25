#include "ReactCollisionWorld.hpp"

#include "ReactHelper.hpp"

Physics::ReactCollisionWorld::ReactCollisionWorld() {}

Physics::ReactCollisionWorld::~ReactCollisionWorld() {}

void Physics::ReactCollisionWorld::InitialiseWorld() {}

void Physics::ReactCollisionWorld::CreateCollisionBody(glm::vec3 position, glm::quat orientation,
                                                       size_t gameObjectID) {
    rp3d::Vector3 bodyPosition       = ReactHelper::ConvertVec3(position);
    rp3d::Quaternion bodyOrientation = ReactHelper::ConvertQuaternion(orientation);
    rp3d::Transform transform(bodyPosition, bodyOrientation);
    rp3d::CollisionBody *body;

    // Creates a react rigid body in this dynamics world
    body = collisionWorld.createCollisionBody(transform);

    ReactCollisionBody reactCollisionBody = ReactCollisionBody(body);

    // Adds the rigid body to the map of rigid bodies
    collisionBodies.insert(std::make_pair(gameObjectID, reactCollisionBody));
}

Physics::CollisionBody *Physics::ReactCollisionWorld::GetCollisionBody(CollisionBodyID bodyID) {
    return &collisionBodies.at(bodyID);
}

bool Physics::ReactCollisionWorld::TestOverlap(CollisionBodyID first, CollisionBodyID seconds) {
    return collisionWorld.testOverlap(collisionBodies.at(first).collisionBody,
                                      collisionBodies.at(seconds).collisionBody);
}

bool Physics::ReactCollisionWorld::TestAABBOverlap(CollisionBodyID first, CollisionBodyID second) {
    return collisionWorld.testAABBOverlap(collisionBodies.at(first).collisionBody,
                                          collisionBodies.at(second).collisionBody);
}
