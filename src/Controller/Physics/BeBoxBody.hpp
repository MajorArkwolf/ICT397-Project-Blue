#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractBody.hpp"

class BeBoxBody : public BeAbstractBody {
  public:
    void CreateBody(glm::vec3 position, glm::quat rotation, BeCollisionWorld *world) override;
    BeCollisionBody *GetBody() override;

  private:
    rp3d::BoxShape shape;
    rp3d::CollisionBody body;
};
