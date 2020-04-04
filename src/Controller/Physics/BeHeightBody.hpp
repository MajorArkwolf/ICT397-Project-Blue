#pragma once

#include "BeAbstractBody.hpp"

class BeHeightBody : public BeAbstractBody {
  public:
    BeHeightBody(glm::vec3 position, glm::quat rotation, int width, int height,
                 BeCollisionWorld *world, float *terrain, beBodyId targetId);

    rp3d::CollisionBody *GetBody() override;
    void SetTransform(glm::vec3 position, glm::quat rotation) override;
    BeTransform *GetTransform() override;
    beBodyId GetId() override;

  private:
    rp3d::HeightFieldShape *shape;
};
