#pragma once

#include "BeAbstractBody.hpp"

class BeSphereBody : public BeAbstractBody {
  public:
    /**
     *  @brief default constructor ~ creates a body
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param radius describes the radius of the sphere
     *  @param world the collision world
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return
     */
    BeSphereBody(glm::vec3 position, glm::quat rotation, float radius,
                 BeCollisionWorld *world, beBodyId targetId);

    /**
     *  @brief Getter for config
     *  @param
     *  @return settings for the world
     */
    rp3d::CollisionBody *GetBody() override;

    /**
     *  @brief Setter ~ allows the collision body position to be updated
     *  @param position the body's position
     *  @param rotation the direction the body is facing
     *  @return
     */
    void SetTransform(glm::vec3 position, glm::quat rotation) override;

    /**
     *  @brief Getter for the body's position
     *  @param
     *  @return BeTransform the facaded class for the react transform class
     */
    BeTransform *GetTransform() override;

    /**
     *  @brief Getter for the body's id
     *  @param
     *  @return the body's id
     */
    beBodyId GetId() override;

  private:
    rp3d::SphereShape *shape;
};
