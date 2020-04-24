#pragma once

#include <reactphysics3d.h>

#include "BeConfig.hpp"
#include "BeMaterial.hpp"
#include "BeTransform.hpp"

class BeAbstractPhysics{
  public:
    /**
     * @brief destructor
     */
    virtual ~BeAbstractPhysics(){}

    /**
     *  @brief abstract method for getting body
     *  @return might be naughty returning a react physics body
     */
    virtual rp3d::RigidBody *GetBody() = 0;

    /**
     *  @brief Setter ~ allows the collision body position to be updated
     *  @param position the body's position
     *  @param rotation the direction the body is facing
     *  @return
     */
    virtual void SetTransform(glm::vec3 position, glm::quat rotation) = 0;

    /**
     *  @brief Getter for the body's position
     *  @param
     *  @return BeTransform the facaded class for the react transform class
     */
    virtual BeTransform GetTransform() = 0 ;

    /**
     *  @brief Getter for the body's id
     *  @param
     *  @return the body's id
     */
    virtual beBodyId GetId() = 0;

    /**
     *  @brief enables gravity
     *  @param gravity boolean for state of gravity
     *  @return
     */
    virtual void EnableGravity(bool gravity) = 0;

    /**
     * @brief set body type
     * @param type rp3d body type enum
     */
    virtual void SetType(BeBodyType type) = 0;

    /**
     * @brief get material to set bounciness and other attributes
     * @return BeMaterial
     */
    virtual BeMaterial &GetMaterial() = 0;

    /**
     * @brief checks rest state
     * @return boolean on sleep state
     */
    virtual bool IsSleepEnabled() = 0;

    /**
     * @brief sets sleep state
     * @param toggle sets sleep boolean
     */
    virtual void SetSleep(bool toggle) = 0;

    /**
     * @brief apply force to dynamic physics object
     * @param force vector representing force in newtons
     */
    virtual void ApplyForceToCentre(const glm::vec3 &force) = 0;

    /**
     * @brief get local vertex given x,y coordinates
     * @param inputX x coord
     * @param inputY y coord
     * @return local vertex
     */
    virtual glm::vec3 GetVertexAt(int inputX, int inputY) = 0;

  protected:
    rp3d::bodyindex bodyId;
    rp3d::Transform transform;
    rp3d::RigidBody *body;

};
