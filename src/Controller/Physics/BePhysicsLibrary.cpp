#include "BePhysicsLibrary.hpp"

BePhysicsLibrary::BePhysicsLibrary(BeAbstractPhysicsFactory *targetFactory) {
    factory = targetFactory;
}

BeAbstractCollision *BePhysicsLibrary::CreateBody(
    glm::vec3 position, glm::quat rotation, glm::vec3 extent, int width,
    int height, float radius, float capsuleHeight, BeCollisionWorld *world,
    float *terrain, ShapeType type, beBodyId targetId) {

    return factory->CreateBody(position, rotation, extent, width, height, radius,
                               capsuleHeight, world, terrain, type, targetId);
}

BeAbstractPhysics *BePhysicsLibrary::CreateBody(
    glm::vec3 position, glm::quat rotation, glm::vec3 extent, float mass, int width,
    int height, float radius, float capsuleHeight, BeDynamicWorld *world,
    float *terrain, ShapeType type, beBodyId targetId) {

    return factory->CreateBody(position, rotation, extent, mass, width, height, radius,
                               capsuleHeight, world, terrain, type, targetId);
}