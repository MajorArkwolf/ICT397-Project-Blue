#include "PhysicsManager.hpp"

auto Physics::PhysicsManager::GetInstance() -> PhysicsManager & {
    static auto instance = PhysicsManager{};
    return instance;
}

Physics::DynamicsWorld *Physics::PhysicsManager::GetDynamicsWorld() {
    return dynamicsWorld.get();
}

Physics::CollisionWorld *Physics::PhysicsManager::GetCollisionWorld() {
    return collisionWorld.get();
}

Physics::ShapeFactory *Physics::PhysicsManager::GetShapeFactory() {
    return shapeFactory.get();
}

void Physics::PhysicsManager::InitialiseCollisionWorld(PhysicsLibrary type) {
    switch (type) {
        case PhysicsLibrary::REACT: {
            collisionWorld = std::make_unique<ReactCollisionWorld>();
        } break;
        default: break;
    }
}

void Physics::PhysicsManager::InitialiseDynamicsWorld(PhysicsLibrary type, glm::vec3 gravity) {
    switch (type) {
        case PhysicsLibrary::REACT: {
            dynamicsWorld = std::make_unique<ReactDynamicsWorld>(gravity);
        } break;
    }
}

void Physics::PhysicsManager::InitialiseShapeFactory(PhysicsLibrary type) {

    switch (type) {
        case PhysicsLibrary::REACT: {
            shapeFactory = std::make_unique<ReactShapes>();
        } break;
    }
}

void Physics::PhysicsManager::LuaInit() {

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<PhysicsManager>("PhysicsManager")
        .addFunction("id", &PhysicsManager::GetDynamicsWorld)
        .addFunction("type", &PhysicsManager::GetCollisionWorld)
        .addFunction("physBody", &PhysicsManager::GetShapeFactory)
        .endClass();

        luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .deriveClass<ReactDynamicsWorld, DynamicsWorld>( "")
        .addFunction("GetRigidBody", &ReactDynamicsWorld::GetRigidBody)
        .addFunction("CreateRigidBody", &ReactDynamicsWorld::CreateRigidBody)
        .endClass();
}
