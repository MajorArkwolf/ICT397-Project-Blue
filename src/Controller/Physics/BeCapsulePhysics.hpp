#pragma once

#include <glm/glm.hpp>

#include "BeAbstractPhysics.hpp"
#include "BeTransform.hpp"
#include "BeScalar.hpp"

class BeDynamicWorld;

class BeCapsulePhysics : public BeAbstractPhysics {
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
    BeCapsulePhysics(glm::vec3 position, glm::quat rotation, float mass, float radius,
    float height, BeDynamicWorld *world, beBodyId targetId);

    /**
     * @brief destructor for shape
     */
    ~BeCapsulePhysics();

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
    BeMaterial GetMaterial() override;

    /**
     * @brief checks rest state
     * @return boolean on sleep state
     */
    bool IsSleepEnabled() override;

    /**
     * @brief sets sleep state
     * @param toggle sets sleep boolean
     */
    void SetSleep(bool toggle) override;

  private:
    rp3d::CapsuleShape *shape;

};

