#pragma once
#include <glm/vec3.hpp>
#include <map>
#include "Controller/PhysicsFacade/ShapeFactory.hpp"
#include <reactphysics3d.h>
#include "Controller/PhysicsFacade/React/ReactCollisionShape.hpp"

namespace Physics {
    class ReactShapes : ShapeFactory{
      public:
        ReactShapes() = default;;
        ~ReactShapes();
        size_t createSphere(float radius) override;
        size_t createBox(glm::vec3 halfExtents) override;
        size_t createCapsule(float radius, float height) override;
        size_t createHeightfield(int columns, int rows, float minHeight, float maxHeight,
                                  float *terrainData) override;
        ReactCollisionShape& GetShape(size_t id);

      private:

        std::map<size_t, ReactCollisionShape> shapeMap;
        size_t GenerateId();


        
    };
}
