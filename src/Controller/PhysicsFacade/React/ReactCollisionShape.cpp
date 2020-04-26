#include "ReactCollisionShape.hpp"

Physics::ReactCollisionShape::ReactCollisionShape(rp3d::CollisionShape *ptr) : shape(ptr) {}

Physics::ReactCollisionShape::ReactCollisionShape(rp3d::CollisionShape *ptr, float *heights)
    : shape(ptr) {
    heightField = heights;
}

std::shared_ptr<rp3d::CollisionShape> Physics::ReactCollisionShape::GetShape() {
    return shape;
}
