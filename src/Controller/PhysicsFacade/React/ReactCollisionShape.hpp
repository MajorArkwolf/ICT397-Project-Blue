#pragma once
#include <map>
#include <reactphysics3d.h>

#include <glm/vec3.hpp>

#include "Controller/PhysicsFacade/ShapeFactory.hpp"

namespace Physics {
    class ReactCollisionShape {
      public:
        ReactCollisionShape(rp3d::CollisionShape *ptr);
        ReactCollisionShape(rp3d::CollisionShape *ptr, float *heights);
        ~ReactCollisionShape();
        std::shared_ptr<rp3d::CollisionShape> GetShape();

      private:
        std::shared_ptr<rp3d::CollisionShape> shape;
        std::shared_ptr<float> heightField;
    };
}
