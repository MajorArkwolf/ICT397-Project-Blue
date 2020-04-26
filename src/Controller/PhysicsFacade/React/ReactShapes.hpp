#pragma once
#include <glm/vec3.hpp>
#include <map>
#include "Controller/PhysicsFacade/ShapeFactory.hpp"
#include <reactphysics3d.h>
#include "Controller/PhysicsFacade/React/ReactCollisionShape.hpp"

namespace Physics {
    class ReactShapes : ShapeFactory{
      public:
        ReactShapes(){};
        ~ReactShapes();
        size_t createSphere(float radius);
        size_t createBox(glm::vec3 halfExtents);
        size_t createCapsule(float radius, float height);
        size_t createHeightfield(int columns, int rows, float minHeight, float maxHeight,
                                  float *terrainData);
        ReactCollisionShape& GetShape(size_t id);

      private:

        std::map<size_t, ReactCollisionShape> shapeMap;
        size_t generateID();


        
    };
}
