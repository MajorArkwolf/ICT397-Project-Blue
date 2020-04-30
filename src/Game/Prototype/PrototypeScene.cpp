#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/GameObject/Manager.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGL.hpp"
#include "View/Renderer/Renderer.hpp"


using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() {
    Init();
}

PrototypeScene::~PrototypeScene() {

}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
    auto &engine = BlueEngine::Engine::get();
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

    terrain.Update(camera.getLocation());
}

void PrototypeScene::Init() {
    auto &engine = BlueEngine::Engine::get();
    camera       = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));
    models.emplace_back("res/model/player_male.obj", false);

    // Temporarily hard-code the external Lua script file while a proper implementation of Lua integration is on hold
    GameObj_Manager::init();
    luaL_dofile(LuaManager::getInstance().getLuaState(), "res/scripts/gameobjsSet.lua");

    auto sphereID     = engine.shapes.createSphere(2);
    auto sphereBodyID = engine.dynWorld.CreateRigidBody(glm::vec3{20, 200, 20}, glm::quat(1, 0, 0, 0));
    auto *reactBodySphere =
        dynamic_cast<Physics::ReactRigidBody *>(engine.dynWorld.GetRigidBody(sphereBodyID));
    reactBodySphere->AddCollisionShape(engine.shapes.GetShape(sphereID), glm::vec3{0, 0, 0},
                                       glm::quat(1, 0, 0, 0), 1.f);

    Blue::HeightMap heightMap;

    terrain.GenerateHeightMap(heightMap);
    auto terrainID = engine.shapes.createHeightfield(heightMap.width - 1, heightMap.height - 1, 0.f,
                                                     217.f, heightMap.terrain);
    auto heightbodyID = engine.dynWorld.CreateRigidBody(glm::vec3{0, 128, 0}, glm::quat(glm::vec3(0,180,0)));
    auto *reactBodyheights =
        dynamic_cast<Physics::ReactRigidBody *>(engine.dynWorld.GetRigidBody(heightbodyID));
    reactBodyheights->AddCollisionShape(engine.shapes.GetShape(terrainID), glm::vec3{0, 0, 0},
                                        glm::quat(1, 0, 0, 0), 1.f);
    reactBodyheights->SetBodyType(2);
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
    auto sphere = engine.dynWorld.GetRigidBody(1)->GetPosition();
    std::cout << static_cast<int>(sphere.x) << ',' << static_cast<int>(sphere.y) << ',' << static_cast<int>(sphere.z) << '\n';
    GameObj_Manager::get(3)->setPos(sphere);
}

void PrototypeScene::unInit() {}
