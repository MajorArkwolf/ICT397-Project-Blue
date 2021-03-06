#include "ReactShapes.hpp"

#include <iostream>

#include "ReactHelper.hpp"
using namespace rp3d;

size_t Physics::ReactShapes::createSphere(float radius) {

    auto id                  = GenerateId();
    rp3d::SphereShape *shape = new rp3d::SphereShape(radius);
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createBox(glm::vec3 halfExtents) {
    auto id               = GenerateId();
    rp3d::BoxShape *shape = new rp3d::BoxShape(ReactHelper::ConvertVec3(halfExtents));
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createCapsule(float radius, float height) {
    auto id                   = GenerateId();
    rp3d::CapsuleShape *shape = new rp3d::CapsuleShape(radius, height);
    shapeMap.emplace(id, ReactCollisionShape(shape));
    return id;
}

size_t Physics::ReactShapes::createHeightField(int columns, int rows, float minHeight,
                                               float maxHeight, float *terrainData) {
    auto id = GenerateId();
    rp3d::HeightFieldShape *shape =
        new rp3d::HeightFieldShape(columns, rows, minHeight, maxHeight, terrainData,
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
