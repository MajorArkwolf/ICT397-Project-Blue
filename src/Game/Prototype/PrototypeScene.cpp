#pragma once
//
// Created by Arkwolf on 19/12/2019.
//
#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Engine/Engine.hpp"
#include "Engine/OpenGL.hpp"
#include "Models/Model.hpp"
#include "Models/ModelManager.hpp"
#include "Renderer/Renderer.hpp"

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
    glLoadIdentity();
    glLineWidth(1);
    auto &engine = BlueEngine::Engine::get();

    SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
    ratio = static_cast<double>(width) / static_cast<double>(height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, ratio, 1, 300);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    models.push_back(ModelManager::GetModelID("../../../res/model/Test/city_residential_03.obj"));
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
            auto &engine = BlueEngine::Engine::get();

            SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
            ratio = static_cast<double>(width) / static_cast<double>(height);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glViewport(0, 0, width, height);
            gluPerspective(60, ratio, 1, 150);
            glMatrixMode(GL_MODELVIEW);

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
    auto &engine = BlueEngine::Engine::get();
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom),
        static_cast<double>(width) / static_cast<double>(height), 0.1, 100000.0);
    glm::mat4 view = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(1.0f);

    Renderer::addToDraw(model, models[0]);

    renderer.draw(view, projection);

    SDL_GL_SwapWindow(engine.window.get());
}

void PrototypeScene::unInit() {}

double PrototypeScene::getDeltaTime() {
    auto &e      = BlueEngine::Engine::get();
    auto newTime = e.getTime();
    return (newTime - time);
}
