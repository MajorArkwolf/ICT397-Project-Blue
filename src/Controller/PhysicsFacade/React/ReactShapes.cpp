#include "ReactShapes.hpp"

#include <iostream>

#include "ReactHelper.hpp"
using namespace rp3d;
Physics::ReactShapes::~ReactShapes() {

    //Handle destruction of heightfield float pointers allocated on the heap
    for (auto &n : heightFields) {
        delete(n);
    }
}
size_t Physics::ReactShapes::createSphere(float radius) {

    auto id = generateID();
    shapeMap.emplace(id, std::make_unique<SphereShape>(radius));
    return id;
}

size_t Physics::ReactShapes::createBox(glm::vec3 halfExtents) {
    auto id = generateID();
    shapeMap.emplace(id, std::make_unique<BoxShape>(ReactHelper::ConvertVec3(halfExtents)));
    return id;
}

size_t Physics::ReactShapes::createCapsule(float radius, float height) {
    auto id = generateID();
    shapeMap.emplace(id, (std::make_unique<rp3d::CapsuleShape>(radius, height)));
    return id;
}

size_t Physics::ReactShapes::createHeightfield(int columns, int rows, float minHeight,
                                               float maxHeight, float *terrainData) {
    auto id = generateID();
    shapeMap.emplace(id, (std::make_unique<rp3d::HeightFieldShape>(columns, rows, minHeight, maxHeight, terrainData, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE)));
    heightFields.push_back(terrainData);
    return id;
}

rp3d::CollisionShape *Physics::ReactShapes::GetShape(size_t id) const {
    return nullptr;
}

size_t Physics::ReactShapes::generateID() {
    static size_t shapeID = 0;
    return shapeID++;
}
