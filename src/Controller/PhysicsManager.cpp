#include "PhysicsManager.hpp"

auto Physics::PhysicsManager::GetInstance() -> PhysicsManager & {
    static auto instance = PhysicsManager{};
    return instance;
}

Physics::DynamicsWorld *Physics::PhysicsManager::GetDynamicsWorld() {
    return dynWorld;
}

Physics::CollisionWorld *Physics::PhysicsManager::GetCollisionWorld() {
    return colWorld;
}

void Physics::PhysicsManager::InitialiseCollisionWorld(PhysicsLibrary type) {
    switch (type) {
        case PhysicsLibrary::REACT: {
            colWorld = new ReactCollisionWorld();
        } break;
        default: break;
    }
}

void Physics::PhysicsManager::InitialiseDynamicsWorld(PhysicsLibrary type, glm::vec3 gravity) {
    switch (type) {
        case PhysicsLibrary::REACT: {
            dynWorld = new ReactDynamicsWorld(gravity);
        } break;
    }
}
