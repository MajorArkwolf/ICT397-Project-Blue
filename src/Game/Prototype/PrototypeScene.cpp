#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/TextureManager.hpp"
#include "Controller/PhysicsManager.hpp"
#include "Model/GameObject/Manager.hpp"
#include "Model/GameObject/Types.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGL.hpp"
#include "View/Renderer/Renderer.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() : dynWorld(glm::vec3(0, -9.8f, 0)) {
    PrototypeScene::Init();
}

PrototypeScene::~PrototypeScene() {}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
    double scalar = 100.0;
    auto &engine  = BlueEngine::Engine::get();

    terrain.Update(camera.getLocation());
    dynWorld.Update(dt);

    if (moveForward) {

         camera.ProcessKeyboard(Camera_Movement::FORWARD, dt);
    }
    if (moveBackward) {

         camera.ProcessKeyboard(Camera_Movement::BACKWARD, dt);
    }
    if (moveLeft) {

         camera.ProcessKeyboard(Camera_Movement::LEFT, dt);
    }
    if (moveRight) {
        
         camera.ProcessKeyboard(Camera_Movement::RIGHT, dt);
    }

    //std::function updateObjects = [&](std::shared_ptr<GameObj_Base> object) {
    //    if (object->gameObj_getTypeID() == 1u || object->gameObj_getTypeID() == 3u) {
    //        auto id             = object->gameObj_physBody;
    //        auto pos            = dynWorld.GetRigidBody(id)->GetPosition();
    //        auto rot            = dynWorld.GetRigidBody(id)->GetOrientation();
    //        object->gameObj_pos = pos;
    //        // object->gameObj_rotation = glm::rotate(rot, object->gameObj_rotation);
    //        // glm::rotate()
    //    }
    //};

    //GameObj_Manager::process_all(updateObjects);
}

void PrototypeScene::Init() {
    auto &engine = BlueEngine::Engine::get();
    camera       = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));

    // Initialise the Physics system
    auto phys_sys = &(Physics::PhysicsManager::GetInstance());
    phys_sys->InitialiseCollisionWorld();
    phys_sys->InitialiseDynamicsWorld();

    // Testing C++ implementation of Game Objects system revision
    vector<BlueEngine::ID> gameObj_ids;
    {
        auto resmanager = ResourceManager::getInstance();
        auto model_id = resmanager.getModelID("res/model/ball.fbx");
        auto phys_world_collision = phys_sys->GetCollisionWorld();
        auto phys_world_dynamics = phys_sys->GetDynamicsWorld();

        auto temp = Controller::Factory::get().GameObject(BlueEngine::ID(GameObj_Type::Static));
        gameObj_ids.push_back(temp->id());
        temp->model = BlueEngine::ID(model_id);
        auto phys_obj_collision = phys_world_collision->GetCollisionBody(temp->physBody);
        phys_obj_collision->SetPosition(glm::vec3(0.0f, 150.0f, -20.0f));
        GameObj_Manager::insert(temp);

        temp = Controller::Factory::get().GameObject(BlueEngine::ID(GameObj_Type::Item));
        gameObj_ids.push_back(temp->id());
        temp->model = BlueEngine::ID(model_id);
        phys_obj_collision = phys_world_collision->GetCollisionBody(temp->physBody);
        phys_obj_collision->SetPosition(glm::vec3(5.0f, 150.0f, -20.0f));
        GameObj_Manager::insert(temp);

        temp = Controller::Factory::get().GameObject(BlueEngine::ID(GameObj_Type::Player));
        gameObj_ids.push_back(temp->id());
        temp->model = BlueEngine::ID(model_id);
        auto phys_obj_rigid = phys_world_dynamics->GetRigidBody(temp->physBody);
        phys_obj_rigid->SetPosition(glm::vec3(10.0f, 150.0f, -20.0f));
        GameObj_Manager::insert(temp);

        temp = Controller::Factory::get().GameObject(BlueEngine::ID(GameObj_Type::NPC));
        gameObj_ids.push_back(temp->id());
        temp->model = BlueEngine::ID(model_id);
        phys_obj_rigid = phys_world_dynamics->GetRigidBody(temp->physBody);
        phys_obj_rigid->SetPosition(glm::vec3(15.0f, 150.0f, -20.0f));
        GameObj_Manager::insert(temp);
    }

    // Temporarily hard-code the external Lua script file while a proper implementation of Lua integration is on hold
   //GameObj_Manager::init();
   //luaL_dofile(LuaManager::getInstance().getLuaState(), "res/scripts/gameobjsSet.lua");

    /*std::function<void(std::shared_ptr<GameObj_Base>)> PhysicsOp =
        [&](std::shared_ptr<GameObj_Base> object) -> void {
        static size_t  gameObjBodyID = 1;
        
            dynWorld.CreateRigidBody(object->gameObj_pos, glm::quat(object->gameObj_rotation), ++gameObjBodyID);
        auto *reactBody =
            dynamic_cast<Physics::ReactRigidBody *>(dynWorld.GetRigidBody(gameObjBodyID));
        if (object->gameObj_getTypeID() == 1u) {
            if (object->gameObj_getModelPath().find("Tree") != std::string::npos) {
                reactBody->AddCollisionShape(shapes.GetShape(TreeShapeID), glm::vec3{0, 0, 0},
                                             glm::quat(1, 0, 0, 0), 1.f);
            } else {
                reactBody->AddCollisionShape(shapes.GetShape(RockShapeID), glm::vec3{0, 0, 0},
                                             glm::quat(1, 0, 0, 0), 1.f);
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

void PrototypeScene::handleInputData(Controller::Input::InputData inputData) {
    auto &engine      = BlueEngine::Engine::get();
    auto &guiManager  = engine.getGuiManager();
    auto handledMouse = false;

    switch (inputData.inputType) {
        case BLUE_InputType::KEY_PRESS: { //  Key Press events

            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                    moveForward = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                    moveBackward = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                    moveLeft = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                    moveRight = true;
                } break;
                case BLUE_InputAction::INPUT_ESCAPE: {
                    guiManager.toggleWindow("menu");
                } break;

                default: break;
            }

        } break;
        case BLUE_InputType::KEY_RELEASE: { // Key Release events
            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                    moveForward = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                    moveBackward = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                    moveLeft = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                    moveRight = false;
                } break;
                case BLUE_InputAction::INPUT_ACTION_2: {
                    auto &renderer = BlueEngine::Engine::get().renderer;
                    renderer.ToggleWireFrame();
                } break;
                case BLUE_InputAction::INPUT_ACTION_3: {
                    guiManager.toggleWindow("instructions");
                } break;
                case BLUE_InputAction::INPUT_ACTION_4: {
                    guiManager.toggleWindow("exit");
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            if (!engine.getMouseMode()) {
                auto x = static_cast<double>(inputData.mouseMotionRelative.x);
                auto y = static_cast<double>(inputData.mouseMotionRelative.y);
                y      = y * -1.0;
                 camera.ProcessMouseMovement(x, y);
                handledMouse = true;
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

auto PrototypeScene::display() -> void {
    auto &engine   = BlueEngine::Engine::get();
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    terrain.AddToDraw();
    GameObj_Manager::addAllToDraw();

}

void PrototypeScene::unInit() {}
