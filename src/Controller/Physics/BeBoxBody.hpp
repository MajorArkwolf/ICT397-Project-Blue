#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractBody.hpp"
#include "BeScalar.hpp"
#include "BeTransform.hpp"

class BeBoxBody : public BeAbstractBody {
  public:
    BeBoxBody(glm::vec3 position, glm::quat rotation, glm::vec3 extent,
              BeCollisionWorld *world, beBodyId targetId);

    rp3d::CollisionBody *GetBody() override;
    void SetTransform(glm::vec3 position, glm::quat rotation) override;
    BeTransform *GetTransform() override;
    beBodyId GetId() override;

  private:
    rp3d::BoxShape *shape;
};
