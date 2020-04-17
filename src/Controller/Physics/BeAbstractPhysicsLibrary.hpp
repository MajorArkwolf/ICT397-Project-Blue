#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeAbstractCollision.hpp"
#include "BeAbstractPhysicsFactory.hpp"

class BeAbstractPhysicsLibrary {
  public:
    /**
     * @brief destructor
     */
    virtual ~BeAbstractPhysicsLibrary() {delete  factory;}

    /**
     *  @brief creates the factory
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param extent only used for BeBoxBody describes the size of the body
     *  @param width only used for BeHeightBody describes the width of the body
     *  @param height only used for BeHeightBody describes the depth of the body
     *  @param radius used in BeSphereBody and BeCapsuleBody describes the radius of the spheres in the body
     *  @param capsuleHeight us in BeCapsuleBody describes the height of the body
     *  @param world the collision world
     *  @param terrain used in BeHeightBody describes the height of the body
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return BeAbstractBody the collision body
     */
    virtual BeAbstractCollision *CreateBody(glm::vec3 position, glm::quat rotation,
                                       glm::vec3 extent, int width, int height,
                                       float radius, float capsuleHeight,
                                       BeCollisionWorld *world, float *terrain,
                                       ShapeType type, beBodyId targetId) = 0;

    /**
     *  @brief creates the factory
     *  @param position the position of the body
     *  @param rotation the orientation of the body
     *  @param extent only used for BeBoxBody describes the size of the body
     *  @param width only used for BeHeightBody describes the width of the body
     *  @param height only used for BeHeightBody describes the depth of the body
     *  @param radius used in BeSphereBody and BeCapsuleBody describes the radius of the spheres in the body
     *  @param capsuleHeight us in BeCapsuleBody describes the height of the body
     *  @param world the collision world
     *  @param terrain used in BeHeightBody describes the height of the body
     *  @param type the type of body to be created
     *  @param targetId the body id
     *  @return BeAbstractBody the collision body
     */
    virtual BeAbstractPhysics *CreateBody(glm::vec3 position, glm::quat rotation,
                                       glm::vec3 extent, float mass, int width, int height,
                                       float radius, float capsuleHeight,
                                       BeDynamicWorld *world, float *terrain,
                                       ShapeType type, beBodyId targetId) = 0;

  protected:
    BeAbstractPhysicsFactory *factory;
};
