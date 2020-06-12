#pragma once
#include <map>
#include <reactphysics3d.h>

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
        ~ReactShapes() = default;
        /**
         * @brief Creates a spherical collision shape with the given radius
         * @param radius The radius of the sphere to create
         * @return the ID of the created shape
         */
        size_t createSphere(float radius) override;
        /**
         * @brief Creates a box with the given halfExtent
         * @param halfExtents The half extents of the box to create
         * @return The id of the created shape
         */
        size_t createBox(glm::vec3 halfExtents) override;
        /**
         * @brief Creates a capsule with the given radius and height
         * @param radius The radius of the capsule
         * @param height The height of the capsule
         * @return The id of the created shape
         */
        size_t createCapsule(float radius, float height) override;

        /**
         * @brief Creates a heightfield with the given parameters
         * @param columns The number of columns in the heightfield
         * @param rows The number of rows in the heightfield
         * @param minHeight The minimum height of the heightfield
         * @param maxHeight the maximum height of the heightfieled
         * @param terrainData The float array containing the array of height values for the terrain
         * @return The id of the created shape
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
