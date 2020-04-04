#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractBody.hpp"
#include "BeAbstractPhysicsFactory.hpp"
#include "BeBoxBody.hpp"
#include "BeCapsuleBody.hpp"
#include "BeCollisionWorld.hpp"
#include "BeConfig.hpp"
#include "BeHeightBody.hpp"
#include "BeSphereBody.hpp"

class BeRP3DFactory : public BeAbstractPhysicsFactory {
  public:
    BeAbstractBody *CreateBody(glm::vec3 position, glm::quat rotation,
                               glm::vec3 extent, int width, int height,
                               float radius, float capsuleHeight,
                               BeCollisionWorld *world, float *terrain,
                               ShapeType type, beBodyId targetId) override;
};
