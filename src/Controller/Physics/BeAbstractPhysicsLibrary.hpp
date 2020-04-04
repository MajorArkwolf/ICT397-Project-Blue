#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractBody.hpp"
#include "BeAbstractPhysicsFactory.hpp"

class BeAbstractPhysicsLibrary {
  public:
    virtual BeAbstractBody *CreateBody(BeAbstractPhysicsFactory *targetFactory,
                                       glm::vec3 position, glm::quat rotation,
                                       glm::vec3 extent, int width, int height,
                                       float radius, float capsuleHeight,
                                       BeCollisionWorld *world, float *terrain,
                                       ShapeType type, beBodyId targetId) = 0;

  protected:
    BeAbstractPhysicsFactory *factory;
};
