#include "BeRP3DFactory.hpp"

BeAbstractBody *BeRP3DFactory::CreateBody(glm::vec3 position, glm::quat rotation,
                                          glm::vec3 extent, int width, int height,
                                          float radius, float capsuleHeight,
                                          BeCollisionWorld *world, float *terrain,
                                          ShapeType type, beBodyId targetId) {
    switch (type) {
        case ShapeType::Box:
            return new BeBoxBody(position, rotation, extent, world, targetId);
        case ShapeType::Height:
            return new BeHeightBody(position, rotation, width, height, world,
                                    terrain, targetId);
        case ShapeType::Sphere:
            return new BeSphereBody(position, rotation, radius, world, targetId);
        case ShapeType::Capsule:
            return new BeCapsuleBody(position, rotation, radius, capsuleHeight,
                                     world, targetId);
        default:
            std::cout << "No shape specified or incorrect shape specified."
                      << std::endl;
            break;
    }
}