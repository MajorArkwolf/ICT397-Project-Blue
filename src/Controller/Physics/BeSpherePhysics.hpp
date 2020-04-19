#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d.h>

#include "BeScalar.hpp"
#include "BeTransform.hpp"
#include "BeAbstractPhysics.hpp"

class BeDynamicWorld;

class BeSpherePhysics : public BeAbstractPhysics{
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
    BeSpherePhysics(glm::vec3 position, glm::quat rotation, float mass, float radius,
        BeDynamicWorld *world, beBodyId targetId);

    /**
     * @brief destructor for body
     */
    ~BeSpherePhysics();

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
    rp3d::SphereShape *shape;
};
