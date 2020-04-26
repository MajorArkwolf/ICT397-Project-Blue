#pragma once
#include <map>

#include <glm/vec3.hpp>

namespace Physics {
    class ShapeFactory {
      public:
        ShapeFactory(){};
        ~ShapeFactory(){};
        virtual size_t createSphere(float radius) = 0;
        virtual size_t createBox(glm::vec3 halfExtents)          = 0;
        virtual size_t createCapsule(float radius, float height) = 0;
        virtual size_t createHeightfield(int columns, int rows, float minHeight, float maxHeight,
                                         float *terrainData)     = 0;
    };
}
