#pragma once

#include <reactphysics3d.h>

#include "BeAbstractBody.hpp"
#include "BeCollisionWorld.hpp"
#include "BeConfig.hpp"

class BeAbstractPhysicsFactory {
  public:
    // need to change shape into enum
    virtual BeAbstractBody *CreateBody(glm::vec3 position, glm::quat rotation,
                                       glm::vec3 extent, int width, int height,
                                       float radius, float capsuleHeight,
                                       BeCollisionWorld *world, float *terrain,
                                       ShapeType type, beBodyId targetId) = 0;
};
