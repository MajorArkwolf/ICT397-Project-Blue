#pragma once

#include "BeAbstractPhysicsLibrary.hpp"

class BePhysicsLibrary : BeAbstractPhysicsLibrary {
    BeAbstractBody *CreateBody(BeAbstractPhysicsFactory *targetFactory,
                               glm::vec3 position, glm::quat rotation,
                               glm::vec3 extent, int width, int height,
                               float radius, float capsuleheight,
                               BeCollisionWorld *world, float *terrain,
                               ShapeType type, beBodyId targetId) override;
};
