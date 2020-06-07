#pragma once
#include <map>

#include <glm/vec3.hpp>

namespace Physics {
    /**
     * @class ShapeFactory
     * @brief An Abstract shape factory used to create collision shapes for use within a collision or rigid body
     */
    class ShapeFactory {
      public:
        /// DEfault constructor
        ShapeFactory(){}
        /// Default destructor
        virtual ~ShapeFactory(){}
        /**
         * @brief Creates a spherical collision shape with the given radius
         * @param radius The radius of the sphere to create
         * @return the ID of the created shape
         */
        virtual size_t createSphere(float radius) = 0;
        /**
         * @brief Creates a box with the given halfExtent
         * @param halfExtents The half extents of the box to create
         * @return The id of the created shape
         */
        virtual size_t createBox(glm::vec3 halfExtents) = 0;
        /**
         * @brief Creates a capsule with the given radius and height
         * @param radius The radius of the capsule
         * @param height The height of the capsule
         * @return The id of the created shape
         */
        virtual size_t createCapsule(float radius, float height) = 0;

        /**
         * @brief Creates a heightfield with the given parameters
         * @param columns The number of columns in the heightfield
         * @param rows The number of rows in the heightfield
         * @param minHeight The minimum height of the heightfield
         * @param maxHeight the maximum height of the heightfieled
         * @param terrainData The float array containing the array of height values for the terrain
         * @return The id of the created shape
         */
        virtual size_t createHeightField(int columns, int rows, float minHeight, float maxHeight,
                                         float *terrainData) = 0;
    };
}
