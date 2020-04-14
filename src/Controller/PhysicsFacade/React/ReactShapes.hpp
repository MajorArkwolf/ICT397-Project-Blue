#pragma once
#include <glm/vec3.hpp>
#include <map>
#include <reactphysics3d.h>
#include <variant>

namespace Physics {
    enum class ShapeType {Sphere, Box, Capsule, Heightfield};
    class ReactShapes {

        using ReactShapeVariant = std::variant< rp3d::SphereShape,  rp3d::BoxShape,  rp3d::CapsuleShape,  rp3d::HeightFieldShape>;


      public:
        ReactShapes(){};
        size_t createSphere(float radius);
        size_t createBox(glm::vec3 halfExtents);
        size_t createCapsule(float radius, float height);
        size_t createHeightfield(int columns, int rows, float minHeight, float maxHeight,
                                  float *terrainData);
        std::map<size_t, std::unique_ptr<rp3d::CollisionShape>> shapeMap;
      private:
        size_t generateID();
        
    };
}
