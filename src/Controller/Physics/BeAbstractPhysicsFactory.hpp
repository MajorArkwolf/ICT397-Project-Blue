#pragma once

#include <reactphysics3d.h>

#include "BeCollisionWorld.hpp"
#include "BeAbstractBody.hpp"

class BeAbstractPhysicsFactory{
  public:
    // need to change shape into enum
    virtual BeAbstractBody *CreateBody(BeCollisionWorld *world, std::string shape) = 0;
};
