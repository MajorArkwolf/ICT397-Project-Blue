#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/PhysicsManager.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/GameObject/Manager.hpp"
#include "Model/GameObject/Types.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGL.hpp"
#include "View/Renderer/Renderer.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

View::Camera *getCamera() {
    return &(BlueEngine::Engine::get().gameStack.getTop()->camera);
}

void toggleWireframe() {
    auto &render = BlueEngine::Engine::get().renderer;
    render.ToggleWireFrame();
}

static float getHeight(float x, float y) {
     return dynamic_cast<PrototypeScene*>(BlueEngine::Engine::get().gameStack.getTop().get())->GetHeightAt(glm::vec2(x,y));
}

PrototypeScene::PrototypeScene() {
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .addFunction("getCamera", &getCamera)
        .addFunction("toggleWireframe", &toggleWireframe)
        .addFunction("getHeightAt", &getHeight);

    PrototypeScene::Init();


    View::Camera::LuaInit();
}

PrototypeScene::~PrototypeScene() {}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
    double scalar = 100.0;
    auto &engine  = BlueEngine::Engine::get();

    terrain.Update(camera.getLocation());

    
    // Update the Dynamic Physics world
    Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->Update(dt);

    if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/luaFunctions.lua")) {
        printf("%s\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
    }
    luabridge::LuaRef Update =
        luabridge::LuaRef::getGlobal(LuaManager::getInstance().getLuaState(), "Update");
    if (!Update.isNil()) {
        Update(dt);
    }
    GameObj_Manager::syncPhys();
}

void PrototypeScene::Init() {
    auto &engine = BlueEngine::Engine::get();
    camera       = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));

    // Initialise the Physics system
    auto phys_sys = &(Physics::PhysicsManager::GetInstance());
    phys_sys->InitialiseCollisionWorld();
    phys_sys->InitialiseDynamicsWorld();
    phys_sys->InitialiseShapeFactory();

    // Initialise the GameObject system
    GameObj_Manager::init();

    // Run the GameObject initialisation script
    if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/gameObjsInit.lua")) {
        printf("%s\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
    }

    // Testing C++ implementation of Game Objects system revision
    // vector<BlueEngine::ID> gameObj_ids;
    //{
    //    const auto ballShape      = phys_sys->GetShapeFactory()->createCapsule(1, 3);
    //    auto resmanager           = ResourceManager::getInstance();
    //    auto model_id             = resmanager.getModelID("res/model/ball.fbx");
    //    auto phys_world_collision = phys_sys->GetCollisionWorld();
    auto *phys_world_dynamics = phys_sys->GetDynamicsWorld();
    auto *phys_world_collision = phys_sys->GetCollisionWorld();

    //    auto temp = Controller::Factory::get().GameObject(GameObj_Type::NPC);
    //    gameObj_ids.push_back(temp->id());
    //    temp->model          = BlueEngine::ID(model_id);
    //    auto *phys_obj_rigid = phys_world_dynamics->GetRigidBody(temp->physBody);
    //    auto *reactBodyheights = dynamic_cast<Physics::ReactRigidBody *>(phys_obj_rigid);
    //    reactBodyheights->AddCollisionShape(dynamic_cast<Physics::ReactShapes*>(phys_sys->GetShapeFactory())->GetShape(ballShape),
    //    glm::vec3(0, 0, 0),
    //                                        glm::quat(glm::vec3(0, 0, 0)), 1);
    //    phys_obj_rigid->SetPosition(glm::vec3(0.0f, 150.0f, -20.0f));
    //    phys_obj_rigid->SetAngularDamping(1.0);
    //    GameObj_Manager::insert(temp);

    //    temp = Controller::Factory::get().GameObject(GameObj_Type::Item);
    //    gameObj_ids.push_back(temp->id());
    //    temp->model             = BlueEngine::ID(model_id);
    //    auto phys_obj_collision = phys_world_collision->GetCollisionBody(temp->physBody);
    //    phys_obj_collision->SetPosition(glm::vec3(5.0f, 150.0f, -20.0f));
    //    GameObj_Manager::insert(temp);

    //    temp = Controller::Factory::get().GameObject(GameObj_Type::Player);
    //    gameObj_ids.push_back(temp->id());
    //    temp->model    = BlueEngine::ID(model_id);
    //    phys_obj_rigid = phys_world_dynamics->GetRigidBody(temp->physBody);
    //    phys_obj_rigid->SetPosition(glm::vec3(10.0f, 150.0f, -20.0f));
    //    GameObj_Manager::insert(temp);

    //    temp = Controller::Factory::get().GameObject(GameObj_Type::NPC);
    //    gameObj_ids.push_back(temp->id());
    //    temp->model    = BlueEngine::ID(model_id);
    //    phys_obj_rigid = phys_world_dynamics->GetRigidBody(temp->physBody);
    //    phys_obj_rigid->SetPosition(glm::vec3(15.0f, 150.0f, -20.0f));
    //    GameObj_Manager::insert(temp);

    //    // Make sure that the physics bodies stay in sync
    //    GameObj_Manager::syncPhys();

    Blue::HeightMap heightMap;
    auto id_assigner = BlueEngine::IDTracker::getInstance();
    terrain.GenerateHeightMap(heightMap);
    const auto terrainID = phys_sys->GetShapeFactory()->createHeightField(
        heightMap.width, heightMap.height, heightMap.heightRange.min, heightMap.heightRange.max,
        heightMap.terrain);
    const auto terrainPhysID = 9999999;


    phys_world_dynamics->CreateRigidBody(heightMap.position, heightMap.rotation, terrainPhysID);
    auto *reactBodyHeights =
        dynamic_cast<Physics::ReactRigidBody *>(phys_world_dynamics->GetRigidBody(terrainPhysID));
    reactBodyHeights->AddCollisionShape(
        dynamic_cast<Physics::ReactShapes *>(phys_sys->GetShapeFactory())->GetShape(terrainID),
        glm::vec3{0, 0, 0}, glm::quat(1, 0, 0, 0), 1.f);
    reactBodyHeights->SetBodyType(Physics::ReactRigidBody::RigidBodyType::STATIC);

    phys_world_collision->CreateCollisionBody(heightMap.position, heightMap.rotation, terrainPhysID);
    auto *reactCollisionBodyHeights =
        dynamic_cast<Physics::ReactCollisionBody *>(phys_world_collision->GetCollisionBody(terrainPhysID));
    reactCollisionBodyHeights->AddCollisionShape(
        dynamic_cast<Physics::ReactShapes *>(phys_sys->GetShapeFactory())->GetShape(terrainID),
        glm::vec3{0, 0, 0}, glm::quat(1, 0, 0, 0));
    //}

    /*std::function<void(std::shared_ptr<GameObj_Base>)> PhysicsOp =
        [&](std::shared_ptr<GameObj_Base> object) -> void {
        static size_t  gameObjBodyID = 1;

            dynWorld.CreateRigidBody(object->gameObj_pos, glm::quat(object->gameObj_rotation),
    ++gameObjBodyID); auto *reactBody = dynamic_cast<Physics::ReactRigidBody
    *>(dynWorld.GetRigidBody(gameObjBodyID)); if (object->gameObj_getTypeID() == 1u) { if
    (object->gameObj_getModelPath().find("Tree") != std::string::npos) {
    reactBody->AddCollisionShape(shapes.GetShape(TreeShapeID), glm::vec3{0, 0, 0}, glm::quat(1, 0,
    0, 0), 1.f); } else { reactBody->AddCollisionShape(shapes.GetShape(RockShapeID), glm::vec3{0, 0,
    0}, glm::quat(1, 0, 0, 0), 1.f);
            }
            reactBody->SetBodyType(2);
        } else {
            reactBody->AddCollisionShape(shapes.GetShape(sphereID), glm::vec3{0, 0, 0},
                                         glm::quat(1, 0, 0, 0), 1.f);
            reactBody->SetBodyType(3);
        }

        object->gameObj_physBody = static_cast<unsigned long>(gameObjBodyID);
    };
    GameObj_Manager::process_all(PhysicsOp);*/
    engine.getGuiManager().setTerrainManager(&terrain);
}

void PrototypeScene::handleWindowEvent() {
    View::OpenGL::ResizeWindow();
}

void PrototypeScene::handleInputData(Controller::Input::InputData inputData, double deltaTime) {

    if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/luaFunctions.lua")) {
        printf("%s\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
    }
    luabridge::LuaRef luaInput =
        luabridge::LuaRef::getGlobal(LuaManager::getInstance().getLuaState(), "handleInput");
    if (!luaInput.isNil()) {
        luaInput(inputData, deltaTime);
    }

    auto &engine      = BlueEngine::Engine::get();
    auto &guiManager  = engine.getGuiManager();
    auto handledMouse = false;

    switch (inputData.inputType) {
        case BLUE_InputType::KEY_PRESS: { //  Key Press events

            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::KEY_RELEASE: { // Key Release events
            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                case BLUE_InputAction::INPUT_JUMP: {
                } break;
                case BLUE_InputAction::INPUT_CROUCH: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_2: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_3: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_4: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            if (!engine.getMouseMode()) {
                /* auto x = static_cast<double>(inputData.mouseMotionRelative.x);
                 auto y = static_cast<double>(inputData.mouseMotionRelative.y);
                 y      = y * -1.0;
                 camera.ProcessMouseMovement(x, y);
                 handledMouse = true;*/
            }
        } break;
        case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
            double amountScrolledY = static_cast<double>(inputData.mouseWheelMotion);
            camera.ProcessMouseScroll(amountScrolledY);
        } break;
        case BLUE_InputType::WINDOW_RESIZE: {
            this->handleWindowEvent();
        } break;
        default: break;
    }
    if (!handledMouse) {
        engine.mouse = {0.0f, 0.0f};
    }
}

float PrototypeScene::GetHeightAt(glm::vec2 coord) {
    return terrain.GetBLHeight(coord);
}

auto PrototypeScene::display() -> void {
    auto &engine   = BlueEngine::Engine::get();
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    terrain.AddToDraw();
    GameObj_Manager::addAllToDraw();
}

void PrototypeScene::unInit() {}
