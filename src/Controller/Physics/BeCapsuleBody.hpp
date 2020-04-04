#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractBody.hpp"

class BeCapsuleBody : public BeAbstractBody {
  public:
    BeCapsuleBody(glm::vec3 position, glm::quat rotation, float radius,
                  float height, BeCollisionWorld *world, beBodyId targetId);
    rp3d::CollisionBody *GetBody() override;
    void SetTransform(glm::vec3 position, glm::quat rotation) override;
    BeTransform *GetTransform() override;
    beBodyId GetId() override;

  private:
    rp3d::CapsuleShape *shape;
};
