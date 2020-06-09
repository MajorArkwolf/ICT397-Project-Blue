#include <View/Renderer/OpenGL.hpp>
#include <Controller/Engine/Engine.hpp>
#include "MainMenu.hpp"
#include "Game/Prototype/PrototypeScene.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

MainMenu::MainMenu() {
    camera = View::Camera();
    camera.Position = glm::vec3(0.0f, 0.0f, 0.0f);
}

MainMenu::~MainMenu() {}

void MainMenu::Init() {
    sModels.emplace_back("res/model/AnimatedHuman.gltf");
    sModels.emplace_back("res/model/AnimatedHuman.gltf");
    sModels.at(0).position.x = 15.0f;
    sModels.at(0).position.z = 1.0f;
    sModels.at(0).rotation = glm::quat(glm::vec3(0.0f, glm::radians(90.0f) ,0.0f));
    sModels.at(1).position.x = 15.0f;
    sModels.at(1).position.z = -1.0f;
    sModels.at(1).rotation = glm::quat(glm::vec3(0.0f, glm::radians(-90.0f) ,0.0f));
}

auto MainMenu::display() -> void {
    auto &engine   = BlueEngine::Engine::get();
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    for (auto& m : sModels) {
        m.addToDraw();
    }
}

auto MainMenu::update(double t, double dt) -> void {

}

void MainMenu::unInit() {

}

void MainMenu::handleWindowEvent() {
    View::OpenGL::ResizeWindow();
}

void MainMenu::handleInputData(Controller::Input::InputData inputData, double deltaTime) {
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
                    //TODO: Move this somewhere useful
                    startGame();
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
//                 auto x = static_cast<double>(inputData.mouseMotionRelative.x);
//                 auto y = static_cast<double>(inputData.mouseMotionRelative.y);
//                 y      = y * -1.0;
//                 camera.ProcessMouseMovement(x, y);
//                 handledMouse = true;
            }
        } break;
        case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
            auto amountScrolledY = static_cast<double>(inputData.mouseWheelMotion);
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

void MainMenu::startGame() {
    auto &engine = BlueEngine::Engine::get();
    engine.gameStack.AddToStack(std::make_shared<PrototypeScene>());
}
