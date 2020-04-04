#include "BePhysicsLibrary.hpp"

BeAbstractBody *BePhysicsLibrary::CreateBody(
    BeAbstractPhysicsFactory *targetFactory, glm::vec3 position, glm::quat rotation,
    glm::vec3 extent, int width, int height, float radius, float capsuleHeight,
    BeCollisionWorld *world, float *terrain, ShapeType type, beBodyId targetId) {
    factory = targetFactory;
    return factory->CreateBody(position, rotation, extent, width, height, radius,
                               capsuleHeight, world, terrain, type, targetId);
}