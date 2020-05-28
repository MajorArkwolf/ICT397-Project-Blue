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

void Physics::PhysicsManager::lua_initialiseReact() {

    GetInstance().InitialiseShapeFactory(PhysicsLibrary::REACT);

    GetInstance().InitialiseCollisionWorld(PhysicsLibrary::REACT);

    GetInstance().InitialiseDynamicsWorld(PhysicsLibrary::REACT);
}

Physics::CollisionWorld *Physics::PhysicsManager::lua_getCollisionWorld() {
    return GetInstance().collisionWorld.get();
}

void GLOBAL_PRINT(int a) {
    std::cout << a;
}

void Physics::PhysicsManager::LuaInit() {

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .addFunction("InitialisePhysics", &lua_initialiseReact)
        .beginNamespace("debug")
        .addFunction("print", &GLOBAL_PRINT)
        .endNamespace();

    // Add glm vectors to lua
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<glm::vec3>("vector")
        .addConstructor<void (*)(float, float, float)>()
        .addProperty("x", &glm::vec3::x)
        .addProperty("y", &glm::vec3::y)
        .addProperty("z", &glm::vec3::z)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<glm::quat>("quaternion")
        .addConstructor<void (*)(float, float, float, float)>()
        .addProperty("x", &glm::quat::x)
        .addProperty("y", &glm::quat::y)
        .addProperty("z", &glm::quat::z)
        .addProperty("w", &glm::quat::w)
        .endClass();

    // Dynamics Worlds and bodies
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<DynamicsWorld>("DynamicsWorld")
        .addFunction("GetRigidBody", &DynamicsWorld::GetRigidBody)
        .addFunction("CreateRigidBody", &DynamicsWorld::CreateRigidBody)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .deriveClass<ReactDynamicsWorld, DynamicsWorld>("ReactDynamicsWorld")
        .addFunction("GetRigidBody", &ReactDynamicsWorld::GetRigidBody)
        .addFunction("CreateRigidBody", &ReactDynamicsWorld::CreateRigidBody)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<RigidBody>("RigidBody")
        .addFunction("GetPosition", &RigidBody::GetPosition)
        .addFunction("GetOrientation", &RigidBody::GetOrientation)
        .addFunction("SetOrientation", &RigidBody::SetOrientation)
        .addFunction("SetPosition", &RigidBody::SetPosition)
        .addFunction("SetPositionAndOrientation", &RigidBody::SetPositionAndOrientation)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .deriveClass<ReactRigidBody, RigidBody>("ReactRigidBody")
        .addFunction("GetPosition", &ReactRigidBody::GetPosition)
        .addFunction("GetOrientation", &ReactRigidBody::GetOrientation)
        .addFunction("SetOrientation", &ReactRigidBody::SetOrientation)
        .addFunction("SetPosition", &ReactRigidBody::SetPosition)
        .addFunction("SetPositionAndOrientation", &ReactRigidBody::SetPositionAndOrientation)
        .addFunction("AddCollisionShape", &ReactRigidBody::AddCollisionShape)
        .addFunction("ApplyForce", &ReactRigidBody::ApplyForce)
        .addFunction("ApplyForceToCentre", &ReactRigidBody::ApplyForceToCentre)
        .addFunction("SetAngularDamping", &ReactRigidBody::SetAngularDamping)
        .addFunction("SetSleeping", &ReactRigidBody::SetSleeping)
        .addFunction("SetMass", &ReactRigidBody::SetMass)
        .addFunction("Destroy", &ReactRigidBody::Destroy)
        .endClass();

    // Shape Factories and shapes
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<ShapeFactory>("ShapeFactory")
        .addFunction("createCapsule", &ShapeFactory::createCapsule)
        .addFunction("createBox", &ShapeFactory::createBox)
        .addFunction("createSphere", &ShapeFactory::createSphere)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .deriveClass<ReactShapes, ShapeFactory>("ReactShapeFactory")
        .addFunction("createCapsule", &ReactShapes::createCapsule)
        .addFunction("createBox", &ReactShapes::createBox)
        .addFunction("createSphere", &ReactShapes::createSphere)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<ReactCollisionShape>("ReactShape")
        .addFunction("GetShape", &ReactCollisionShape::GetShape)
        .endClass();

    // Collision worlds and bodies
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<CollisionBody>("CollisionBody")
        .addFunction("GetPosition", &CollisionBody::GetPosition)
        .addFunction("GetOrientation", &CollisionBody::GetOrientation)
        .addFunction("SetOrientation", &CollisionBody::SetOrientation)
        .addFunction("SetPosition", &CollisionBody::SetPosition)
        .addFunction("SetPositionAndOrientation", &CollisionBody::SetPositionAndOrientation)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<CollisionWorld>("CollisionWorld")
        .addFunction("GetCollisionBody", &CollisionWorld::GetCollisionBody)
        .addFunction("CreateCollisionBody", &CollisionWorld::CreateCollisionBody)
        .endClass();


    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginClass<PhysicsManager>("PhysicsManager")
        .addStaticFunction("GetInstance", &PhysicsManager::GetInstance)
        .addFunction("GetCollisionWorld", &PhysicsManager::GetCollisionWorld)
        .addFunction("GetDynamicsWorld", &PhysicsManager::GetDynamicsWorld)
        .addFunction("GetShapeFactory", &PhysicsManager::GetShapeFactory)
        .endClass();
}

Physics::PhysicsManager::PhysicsManager() {
    LuaInit();
}
