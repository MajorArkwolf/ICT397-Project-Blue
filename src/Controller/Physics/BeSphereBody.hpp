#pragma once

#include "BeAbstractBody.hpp"

class BeSphereBody : public BeAbstractBody {
  public:
    BeSphereBody(glm::vec3 position, glm::quat rotation, float radius,
                 BeCollisionWorld *world, beBodyId targetId);
    rp3d::CollisionBody *GetBody() override;
    void SetTransform(glm::vec3 position, glm::quat rotation) override;
    BeTransform *GetTransform() override;
    beBodyId GetId() override;

  private:
    rp3d::SphereShape *shape;
};
