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

PrototypeScene::PrototypeScene() : dynWorld(glm::vec3(0, -9.8f, 0)) {
    Init();
}

PrototypeScene::~PrototypeScene() {}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
    double scalar = 100.0;
    auto &engine  = BlueEngine::Engine::get();
    auto sphere   = dynWorld.GetRigidBody(0);

    terrain.Update(camera.getLocation());
    dynWorld.Update(dt);

    camera.Position = sphere->GetPosition() + glm::vec3(10, 10, 10);

    auto radians      = curremtRot * ((std::atan(1) * 4) / 180);
    camera.Position.x = std::cos(radians) * 15;
    camera.Position.z = std::sin(radians) * 15;

    camera.Position += sphere->GetPosition();
    camera.Position.y = sphere->GetPosition().y + currentDist;
    camera.Front = glm::normalize(static_cast<glm::dvec3>(sphere->GetPosition()) - camera.Position);
    camera.Position.y += 5;

    if (moveForward) {
        sphere->ApplyForceToCentre(camera.Front * scalar);
        // camera.ProcessKeyboard(Camera_Movement::FORWARD, dt);
    }
    if (moveBackward) {
        sphere->ApplyForceToCentre(-camera.Front * scalar);
        // camera.ProcessKeyboard(Camera_Movement::BACKWARD, dt);
    }
    if (moveLeft) {
        sphere->ApplyForceToCentre(-camera.GetRightVector() * scalar);
        // camera.ProcessKeyboard(Camera_Movement::LEFT, dt);
    }
    if (moveRight) {
        sphere->ApplyForceToCentre(camera.GetRightVector() * scalar);
        // camera.ProcessKeyboard(Camera_Movement::RIGHT, dt);
    }

    std::function updateObjects = [&](std::shared_ptr<GameObj_Base> object) {
        if (object->gameObj_getTypeID() == 1u || object->gameObj_getTypeID() == 3u) {
            auto id             = object->gameObj_physBody;
            auto pos            = dynWorld.GetRigidBody(id)->GetPosition();
            auto rot            = dynWorld.GetRigidBody(id)->GetOrientation();
            object->gameObj_pos = pos;
            // object->gameObj_rotation = glm::rotate(rot, object->gameObj_rotation);
            // glm::rotate()
        }
    };

    GameObj_Manager::process_all(updateObjects);
}

void PrototypeScene::Init() {
    auto &engine = BlueEngine::Engine::get();
    camera       = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));

    // Temporarily hard-code the external Lua script file while a proper implementation of Lua integration is on hold
    GameObj_Manager::init();
    luaL_dofile(LuaManager::getInstance().getLuaState(), "res/scripts/gameobjsSet.lua");

    auto sphereID     = shapes.createSphere(1);
    size_t sphereBodyID = 0;
    dynWorld.CreateRigidBody(glm::vec3{20, 170, 20}, glm::quat(1, 0, 0, 0), sphereBodyID);
    auto *reactBodySphere =
        dynamic_cast<Physics::ReactRigidBody *>(dynWorld.GetRigidBody(sphereBodyID));
    reactBodySphere->AddCollisionShape(shapes.GetShape(sphereID), glm::vec3{0, 0, 0},
                                       glm::quat(1, 0, 0, 0), 1.f);
    reactBodySphere->SetMass(10.f);

    Blue::HeightMap heightMap;

    terrain.GenerateHeightMap(heightMap);
    auto terrainID =
        shapes.createHeightfield(heightMap.width, heightMap.height, heightMap.heightRange.min,
                                 heightMap.heightRange.max, heightMap.terrain);
    size_t heightbodyID = 1;
    dynWorld.CreateRigidBody(heightMap.position, heightMap.rotation, heightbodyID );
    auto *reactBodyheights =
        dynamic_cast<Physics::ReactRigidBody *>(dynWorld.GetRigidBody(heightbodyID));
    reactBodyheights->AddCollisionShape(shapes.GetShape(terrainID), glm::vec3{0, 0, 0},
                                        glm::quat(1, 0, 0, 0), 1.f);
    reactBodyheights->SetBodyType(2);

    auto TreeShapeID = shapes.createBox(glm::vec3(2, 10, 2));
    auto RockShapeID = shapes.createBox(glm::vec3(3, 2, 3));

    std::function<void(std::shared_ptr<GameObj_Base>)> PhysicsOp =
        [&](std::shared_ptr<GameObj_Base> object) -> void {
        static size_t  gameObjBodyID = 2;
        
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
    GameObj_Manager::process_all(PhysicsOp);
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
                curremtRot += x * 0.5;
                currentDist += y *0.5;
                if (currentDist < 5) {
                    currentDist = 5;
                }
                if (currentDist > 40) {
                    currentDist = 40;
                    }
                // camera.ProcessMouseMovement(x, y);
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
    auto sphere = dynWorld.GetRigidBody(1)->GetPosition();
    GameObj_Manager::get(3)->setPos(sphere);

    // glm::vec3 orientation(engine.dynWorld.GetRigidBody(1)->GetOrientation());
    // GameObj_Manager::get(3)
}

void PrototypeScene::unInit() {}
