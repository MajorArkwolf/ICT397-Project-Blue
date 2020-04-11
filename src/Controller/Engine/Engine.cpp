#include "Controller/Engine/Engine.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "BaseState.hpp"
#include "GameStack.hpp"

#include "Controller/InputManager.hpp"
#include "Controller/GUIManager.hpp"

#define GLEQ_IMPLEMENTATION
#define GLEQ_STATIC
#include "gleq.h"

// Game States
#include "Game/Prototype/PrototypeScene.hpp"

using BlueEngine::Engine;
using std::runtime_error;
using std::string;

/**
 * @brief The game engine main loop
 */
auto Engine::run() -> void {
    auto &engine = Engine::get();

    auto *prototype = new PrototypeScene();
    engine.gameStack.AddToStack(prototype);

    double t  = 0.0;
    double dt = 0.01;

    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    // State previous;
    // State current;
    // State state;
    glfwFocusWindow(engine.window);
    while (engine.getIsRunning()) {
        double newTime   = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt) {
            // previousState = currentState;
            engine.processInput();
            engine.gameStack.getTop()->update(t, dt);
            t += dt;
            accumulator -= dt;
        }
        const double alpha = accumulator / dt;
        // state = currentState * alpha + previousState * (1.0 - alpha);

        engine.gameStack.getTop()->display();
    }
}

//GUIManager& BlueEngine::Engine::getGuiManager() {
//    return guiManager;
//}

/**
 * @brief Game engine default constructor, sets up all variables and settings required for operation
 */
Engine::Engine() {
    getBasePath();
    if (!glfwInit()) {
        std::cerr << "GLFW FAILED TO INIT \n";
    }
    gleqInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(800, 600, "Project Blue", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    gleqTrackWindow(window);
    glfwMakeContextCurrent(window);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    //this->guiManager.initialiseImGUI(this->window.get(), this->context.get());


}

/**
 * @brief Engine default destructor
 * Safely closes Engine and frees memory
 */
Engine::~Engine() {
    glfwTerminate();
}

/**
 * @brief Returns the current instance of the engine
 * @return The current engine instance
 */
auto Engine::get() -> Engine & {
    static auto instance = Engine{};

    return instance;
}

auto Engine::processInput() -> void {
    auto event        = GLEQevent{};
    auto handledMouse = true;
    //auto &inputManager = Controller::Input::InputManager::getInstance();

    while (gleqNextEvent(&event)) {
        //if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.type == SDL_KEYDOWN) {
        //    relativeMouseMode = relativeMouseMode ? SDL_FALSE : SDL_TRUE;
        //    SDL_SetRelativeMouseMode(relativeMouseMode);
        //}
        //ImGui_ImplSDL2_ProcessEvent(&event);
        //gameStack.getTop()->handleInputData(inputManager.ProcessInput(event));
    }
    if (!handledMouse) {
        this->mouse = {0.0f, 0.0f};
    }
}

auto Engine::getIsRunning() const -> bool {
    return this->isRunning;
}

auto Engine::endEngine() -> void {    
    glfwDestroyWindow(window);
    isRunning = false;
}

auto Engine::getBasePath() -> void {
    //char *base_path = SDL_GetBasePath();
    //basepath        = std::string(base_path);
    //SDL_free(base_path);
    basepath = ".";
}
