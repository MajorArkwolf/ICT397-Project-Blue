#pragma once

#include "BeAbstractPhysicsFactory.hpp"
#include "BeAbstractBody.hpp"
#include "BeCollisionWorld.hpp"

class BeRP3DFactory: public BeAbstractPhysicsFactory {
  public:
    BeAbstractBody *CreateBody(BeCollisionWorld *world) override;
};
