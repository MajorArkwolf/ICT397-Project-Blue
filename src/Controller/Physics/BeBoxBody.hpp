#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractCollision.hpp"
#include "BeScalar.hpp"
#include "BeTransform.hpp"

class BeBoxBody : public BeAbstractCollision {
  public:
    /**
     *  @brief default constructor ~ creates a body
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param extent only used for BeBoxBody describes the size of the body
     *  @param world the collision world
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return BeAbstractBody the collision body
     */
    BeBoxBody(glm::vec3 position, glm::quat rotation, glm::vec3 extent,
              BeCollisionWorld *world, beBodyId targetId);

    /**
     * @brief destructor for the body
     */
    ~BeBoxBody();

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
    rp3d::BoxShape *shape;
};
