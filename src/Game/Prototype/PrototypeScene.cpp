#include "PrototypeScene.hpp"
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_sdl.cpp>
#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGLProxy.hpp"
#include "View/Renderer/Renderer.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() {
    Init();
}

auto PrototypeScene::update(double t, double dt) -> void {
    if (moveForward) {
        camera.ProcessKeyboard(FORWARD, dt);
    }
    if (moveBackward) {
        camera.ProcessKeyboard(BACKWARD, dt);
    }
    if (moveLeft) {
        camera.ProcessKeyboard(LEFT, dt);
    }
    if (moveRight) {
        camera.ProcessKeyboard(RIGHT, dt);
    }
}

void PrototypeScene::Init() {
    BlueEngine::RenderCode::HardInit();
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
     models.push_back(ModelManager::GetModelID("res/model/IronMan/IronMan.obj"));
}

void PrototypeScene::handleWindowEvent(SDL_Event &event) {
    switch (event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESIZED: {
            BlueEngine::RenderCode::ResizeWindow();
        } break;
        default: break;
    }
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
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            auto x = static_cast<float>(inputData.mouseMotionRelative.x);
            auto y = static_cast<float>(inputData.mouseMotionRelative.y);
            y      = y * -1.0f;
            camera.ProcessMouseMovement(x, y);
            handledMouse = true;
        } break;
        case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
            int amountScrolledY = inputData.mouseWheelMotion;
            camera.ProcessMouseScroll(amountScrolledY);
        }
    }
    if (!handledMouse) {
        engine.mouse = {0.0f, 0.0f};
    }
}

auto PrototypeScene::display() -> void {

    auto &engine = BlueEngine::Engine::get();
    auto &inputManager = Controller::Input::InputManager::getInstance();
    auto &guiManager   = engine.getGuiManager();

   /* ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(stonk.window.get());*/
    guiManager.startWindowFrame();
    guiManager.displayInputRebindWindow();
    guiManager.displayEscapeMenu();

    BlueEngine::RenderCode::Display();
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                            static_cast<double>(display.w) /
                                                static_cast<double>(display.h),
                                            0.1, 100000.0);
    glm::mat4 view       = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(5.0f);

     Renderer::addToDraw(model, models[0]);

    renderer.draw(view, projection);

    guiManager.endWindowFrame();

    BlueEngine::RenderCode::EndDisplay();
}

void PrototypeScene::unInit() {}

double PrototypeScene::getDeltaTime() {
    auto &e      = BlueEngine::Engine::get();
    auto newTime = e.getTime();
    return (newTime - time);
}
