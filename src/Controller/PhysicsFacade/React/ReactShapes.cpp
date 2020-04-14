#include "ReactShapes.hpp"
#include "ReactHelper.hpp"
#include <iostream>
using namespace rp3d;
size_t Physics::ReactShapes::createSphere(float radius) {
    
    auto id = generateID();
    shapeMap.emplace(id, std::make_unique<CollisionShape>(rp3d::SphereShape{radius}));
    return id;


}

size_t Physics::ReactShapes::createBox(glm::vec3 halfExtents) {
    auto id = generateID();
   // shapeMap.emplace(id, (std::in_place_type<rp3d::BoxShape>, ReactHelper::ConvertVec3(halfExtents)));
    return id;
}

size_t Physics::ReactShapes::createCapsule(float radius, float height) {
    auto id = generateID();

    ReactShapeVariant asd{
        std::in_place_type<rp3d::CapsuleShape>, radius, height};

    //shapeMap.emplace(id, (std::in_place_type<rp3d::CapsuleShape>, radius, height));
    //rp3d::C
    return id;
}

size_t Physics::ReactShapes::createHeightfield(int columns, int rows, float minHeight,
                                               float maxHeight, float *terrainData) {

    return size_t();
}

size_t Physics::ReactShapes::generateID() {
    static size_t shapeID = 0;
    return shapeID++;
}
