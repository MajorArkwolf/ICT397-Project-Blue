#pragma once

#include <glm/glm.hpp>
#include "BeScalar.hpp"
#include "BeTransform.hpp"
#include "BeAbstractPhysics.hpp"

class BeDynamicWorld;

class BeHeightPhysics : public BeAbstractPhysics{
  public:
    /**
     *  @brief default constructor ~ creates a body
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param width only used for BeHeightBody describes the width of the body
     *  @param height describes the depth of the body
     *  @param world the collision world
     *  @param terrain decribes the height of the body
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return
     */
    BeHeightPhysics(glm::vec3 position, glm::quat rotation, float mass, int width, int height,
        BeDynamicWorld *world, float *terrain, beBodyId targetId);

    /**
     *  @brief Getter for config
     *  @param
     *  @return settings for the world
     */
    rp3d::RigidBody *GetBody() override;

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
    rp3d::HeightFieldShape *shape;
};
