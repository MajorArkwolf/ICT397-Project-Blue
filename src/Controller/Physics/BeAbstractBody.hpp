#pragma once

#include <reactphysics3d.h>

#include "BeScalar.hpp"
#include "BeTransform.hpp"

class BeCollisionWorld;

class BeAbstractBody {
  public:
    virtual rp3d::CollisionBody *GetBody()                            = 0;
    virtual void SetTransform(glm::vec3 position, glm::quat rotation) = 0;
    virtual BeTransform *GetTransform()                               = 0;
    virtual beBodyId GetId()                                          = 0;

  protected:
    rp3d::bodyindex bodyId;
    rp3d::Transform transform;
    rp3d::CollisionBody *body;
};
