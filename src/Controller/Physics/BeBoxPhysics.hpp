#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "BeScalar.hpp"
#include "BeTransform.hpp"
#include "BeAbstractPhysics.hpp"

class BeDynamicWorld;

class BeBoxPhysics: public BeAbstractPhysics {
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
    BeBoxPhysics(glm::vec3 position, glm::quat rotation, glm::vec3 extent, beScalar mass,
    BeDynamicWorld *world, beBodyId targetId);

    ~BeBoxPhysics();

    /**
     *  @brief concrete method for getting body
     *  @return might be naughty returning a react physics body
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
    BeTransform GetTransform() override;

    /**
     *  @brief Getter for the body's id
     *  @param
     *  @return the body's id
     */
    beBodyId GetId() override;

    /**
     *  @brief enables gravity
     *  @param gravity boolean for state of gravity
     *  @return
     */
    void EnableGravity(bool gravity) override;

    /**
     * @brief set body type
     * @param type rp3d body type enum
     */
    void SetType(BeBodyType type) override;

    /**
     * @brief get material to set bounciness and other attributes
     * @return BeMaterial
     */
    BeMaterial *GetMaterial() override;

  private:
    rp3d::BoxShape *shape;
};
