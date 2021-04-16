#pragma once
#include <map>
#include <reactphysics3d/reactphysics3d.h>

#include <glm/vec3.hpp>

#include "Controller/PhysicsFacade/React/ReactCollisionShape.hpp"
#include "Controller/PhysicsFacade/ShapeFactory.hpp"

namespace Physics {

    /**
     *@class ReactShapes
     *@brief A class used to make and store shapes used in React collision bodies
     */
    class ReactShapes final : public ShapeFactory {
      public:
        ReactShapes()  = default;

        ~ReactShapes() override;

        /**
         *@see ShapeFactory::createSphere
         */
        size_t createSphere(float radius) override;

        /**
         *@see ShapeFactory::createBox
         */
        size_t createBox(glm::vec3 halfExtents) override;

        /**
         *@see ShapeFactory::createCapsule
         */
        size_t createCapsule(float radius, float height) override;

        /**
         *@see ShapeFactory::createHeightField
         */
        size_t createHeightField(int columns, int rows, float minHeight, float maxHeight,
                                 float *terrainData) override;

        /**
         *@brief Returns the shape at the given ID
         */
        ReactCollisionShape &GetShape(size_t id);

      private:
        std::map<size_t, ReactCollisionShape> shapeMap;
        size_t GenerateId();
    };
}
