#include "ReactCollisionShape.hpp"
#include "PhysicsSingleton.hpp"

Physics::ReactCollisionShape::ReactCollisionShape(rp3d::CollisionShape *ptr) : shape(ptr) {

}

Physics::ReactCollisionShape::ReactCollisionShape(rp3d::CollisionShape *ptr, float *heights)
    : shape(ptr), heightField(heights) {}

Physics::ReactCollisionShape::~ReactCollisionShape() {
//    auto &physicsCommon = PhysicsSingleton::getInstance().getPhysicsCommon();
//    //TRIANGLE, SPHERE, CAPSULE, BOX, CONVEX_MESH, TRIANGLE_MESH, HEIGHTFIELD
//    if (shape->getName() == rp3d::CollisionShapeName::SPHERE) {
//    } else if (shape->getName() == rp3d::CollisionShapeName::SPHERE) {
//
//    } else if(shape->getName() == rp3d::CollisionShapeName::CAPSULE) {
//
//    } else if (shape->getName() == rp3d::CollisionShapeName::CONVEX_MESH) {
//
//    }else if (shape->getName() == rp3d::CollisionShapeName::TRIANGLE_MESH) {
//
//    }else if (shape->getName() == rp3d::CollisionShapeName::HEIGHTFIELD) {
//
//    } else {
//        assert(false);
//    }
}

std::shared_ptr<rp3d::CollisionShape> Physics::ReactCollisionShape::GetShape() {
    return shape;
}
