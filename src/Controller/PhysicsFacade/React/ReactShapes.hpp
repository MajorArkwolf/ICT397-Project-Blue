#pragma once
#include <glm/vec3.hpp>
#include <map>
#include <reactphysics3d.h>

namespace Physics {
    class ReactShapes{
      public:
        ReactShapes(){};
        ~ReactShapes();
        size_t createSphere(float radius);
        size_t createBox(glm::vec3 halfExtents);
        size_t createCapsule(float radius, float height);
        size_t createHeightfield(int columns, int rows, float minHeight, float maxHeight,
                                  float *terrainData);


      private:
        rp3d::CollisionShape *GetShape(size_t id) const;
        std::map<size_t, std::unique_ptr<rp3d::CollisionShape>> shapeMap;
        std::vector<float *> heightFields;
        size_t generateID();


        
    };
}
