#pragma once

#include <reactphysics3d.hpp>

#include "BeCollisionWorld.hpp"
#include "BeCollisionBody.hpp"

class BePhysicsAbstract{
  public:
    virtual  void CreateBody(glm::vec3 position, glm::quat rotation, BeCollisionWorld *world) = 0;
    virtual BeCollisionBody *GetBody() = 0;

  private:
    rp3d::CollisionBody *body;
    rp3d::CollisionWorld *world;

};
