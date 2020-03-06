#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/Engine/OpenGL.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/Renderer.hpp"
#include "View/Renderer/OpenGLProxy.hpp"

PrototypeScene::PrototypeScene() {
    softInit();
}

auto PrototypeScene::update(double dt) -> void {
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

void PrototypeScene::hardInit() {
    BlueEngine::RenderCode::HardInit();
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    models.push_back(ModelManager::GetModelID("res/model/Test/city_residential_03.obj"));

}

void PrototypeScene::softInit() {
    hardInit();
}

void PrototypeScene::handleInput(SDL_Event &event) {
    auto &engine      = BlueEngine::Engine::get();
    auto handledMouse = false;
    switch (event.type) {
        case SDL_WINDOWEVENT: {
            this->handleWindowEvent(event);
        } break;
        case SDL_KEYDOWN: {
            this->handleKeyPress(event);
        } break;
        case SDL_KEYUP: {
            this->handleKeyRelease(event);
        } break;
        case SDL_MOUSEMOTION: {
            this->handleMouseMovement(event);
            handledMouse = true;
        } break;
        case SDL_MOUSEWHEEL: {
            this->handleMouseScroll(event);
        } break;
        default: break;
    }
    if (!handledMouse) {
        engine.mouse = {0.0f, 0.0f};
    }
}

void PrototypeScene::handleMouseScroll(SDL_Event &event) {
    int amountScrolledY = event.wheel.y;
    camera.ProcessMouseScroll(amountScrolledY);
}

void PrototypeScene::handleMouseMovement(SDL_Event &event) {
    auto x = static_cast<float>(event.motion.xrel);
    auto y = static_cast<float>(event.motion.yrel);
    y      = y * -1;
    camera.ProcessMouseMovement(x, y);
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

void PrototypeScene::handleKeyPress(SDL_Event &event) {

    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W: {
            moveForward = true;
        } break;
        case SDL_SCANCODE_S: {
            moveBackward = true;
        } break;
        case SDL_SCANCODE_A: {
            moveLeft = true;
        } break;
        case SDL_SCANCODE_D: {
            moveRight = true;
        } break;
        case SDL_SCANCODE_ESCAPE: {
            auto &engine = BlueEngine::Engine::get();
            engine.endEngine();
        } break;
    }
}

void PrototypeScene::handleKeyRelease(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W: {
            moveForward = false;
        } break;
        case SDL_SCANCODE_S: {
            moveBackward = false;
        } break;
        case SDL_SCANCODE_A: {
            moveLeft = false;
        } break;
        case SDL_SCANCODE_D: {
            moveRight = false;
        } break;
        case SDL_SCANCODE_ESCAPE: {

        } break;
    }
}

auto PrototypeScene::display() -> void {
    BlueEngine::RenderCode::Display();
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);
    // view/projection transformations
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom),
        static_cast<double>(display.w) / static_cast<double>(display.h), 0.1, 100000.0);
    glm::mat4 view = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(5.0f);

    Renderer::addToDraw(model, models[0]);

    renderer.draw(view, projection); 
    BlueEngine::RenderCode::EndDisplay();
}

void PrototypeScene::unInit() {}

double PrototypeScene::getDeltaTime() {
    auto &e      = BlueEngine::Engine::get();
    auto newTime = e.getTime();
    return (newTime - time);
}
