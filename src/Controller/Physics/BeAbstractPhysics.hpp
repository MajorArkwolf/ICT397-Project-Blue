#pragma once

#include <reactphysics3d.h>
#include "BeTransform.hpp"

class BeAbstractPhysics{
  public:
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
    virtual BeTransform *GetTransform() = 0 ;

    /**
     *  @brief Getter for the body's id
     *  @param
     *  @return the body's id
     */
    virtual beBodyId GetId() = 0;

  protected:
    rp3d::bodyindex bodyId;
    rp3d::Transform transform;
    rp3d::RigidBody *body;

};
