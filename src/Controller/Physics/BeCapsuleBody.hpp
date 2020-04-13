#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractCollision.hpp"

class BeCollisionWorld;

class BeCapsuleBody : public BeAbstractCollision {
  public:
    /**
     *  @brief default constructor ~ creates a body
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param radius only used for BeCapsulebody describes the size of the sphere
     *  @param height used to describe the height of the capsule
     *  @param world the collision world
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return BeAbstractBody the collision body
     */
    BeCapsuleBody(glm::vec3 position, glm::quat rotation, float radius,
                  float height, BeCollisionWorld *world, beBodyId targetId);

    /**
     *  @brief concrete method for getting body
     *  @return might be naughty returning a react physics body
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
    rp3d::CapsuleShape *shape;
};