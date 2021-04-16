#include "ReactShapes.hpp"
#include "PhysicsSingleton.hpp"
#include <iostream>

#include "ReactHelper.hpp"
using namespace rp3d;


size_t Physics::ReactShapes::createSphere(float radius) {
    auto& physicsCommon = PhysicsSingleton::getInstance().getPhysicsCommon();
    auto id                  = GenerateId();
    rp3d::SphereShape *shape = physicsCommon.createSphereShape(radius);
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createBox(glm::vec3 halfExtents) {
    auto& physicsCommon = PhysicsSingleton::getInstance().getPhysicsCommon();
    auto id               = GenerateId();
    rp3d::BoxShape *shape = physicsCommon.createBoxShape(ReactHelper::ConvertVec3(halfExtents));
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createCapsule(float radius, float height) {
    auto& physicsCommon = PhysicsSingleton::getInstance().getPhysicsCommon();
    auto id                   = GenerateId();
    rp3d::CapsuleShape *shape = physicsCommon.createCapsuleShape(radius, height);
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createHeightField(int columns, int rows, float minHeight,
                                               float maxHeight, float *terrainData) {
    auto& physicsCommon = PhysicsSingleton::getInstance().getPhysicsCommon();
    auto id = GenerateId();
    rp3d::HeightFieldShape *shape =
            physicsCommon.createHeightFieldShape(columns, rows, minHeight, maxHeight, terrainData,
                                   rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
    shapeMap.emplace(id, ReactCollisionShape(shape, terrainData));
    return id;
}

Physics::ReactCollisionShape& Physics::ReactShapes::GetShape(size_t id) {
    return shapeMap.at(id);
}

size_t Physics::ReactShapes::GenerateId() {
    static size_t shapeID = 0;
    return shapeID++;
}

Physics::ReactShapes::~ReactShapes() {

}
