#include "Controller/Engine/Engine.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "BaseState.hpp"
#include "Controller/GUIManager.hpp"
#include "Controller/InputManager.hpp"
#include "Controller/ResourceManager.hpp"
#include "GameStack.hpp"
#include "Controller/PhysicsFacade/React/ReactShapes.hpp"

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
    ResourceManager::getInstance().loadResources();
    while (engine.getIsRunning()) {
        double newTime   = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt) {
            // previousState = currentState;
            glfwPollEvents();
            engine.processInput();
            engine.gameStack.getTop()->update(t, dt);
            t += dt;
            accumulator -= dt;
        }
        const double alpha = accumulator / dt;
        // state = currentState * alpha + previousState * (1.0 - alpha);

        engine.gameStack.getTop()->display();
    }
    glfwDestroyWindow(engine.window);
}

GUIManager &BlueEngine::Engine::getGuiManager() {
    return guiManager;
}

/**
 * @brief Game engine default constructor, sets up all variables and settings required for operation
 */
Engine::Engine() : dynWorld(glm::vec3{0, -9.8, 0}) {
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

    this->guiManager.initialiseImGUI(window);
    Physics::ReactShapes shapes;
    auto id = shapes.createSphere(5);
    std::cout << id;
    auto &sphereShape = shapes.shapeMap.at(id);
    try {
        auto &w = std::get<0>(sphereShape);
        std::cout << w.getRadius();
    } catch (std::bad_variant_access &) {
    }


    
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
    GLEQevent event;
    auto handledMouse  = true;
    auto &inputManager = Controller::Input::InputManager::getInstance();

    while (gleqNextEvent(&event)) {
        if (event.type == GLEQ_KEY_PRESSED || event.type == GLEQ_KEY_RELEASED) {
            inputManager.recordKeyStates(event);
        }
        switch (event.type) {
            case GLEQ_KEY_PRESSED: {
                if (event.keyboard.key == GLFW_KEY_F1) {
                    auto mouseMode = glfwGetInputMode(window, GLFW_CURSOR);
                    if (mouseMode == GLFW_CURSOR_NORMAL) {
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    } else {
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    }
                }
            } break;
            case GLEQ_WINDOW_CLOSED: {
                this->endEngine();
            } break;
            default: break;
        }

        gameStack.getTop()->handleInputData(inputManager.ProcessInput(event));
        gleqFreeEvent(&event);
    }
    if (!handledMouse) {
        this->mouse = {0.0f, 0.0f};
    }
}

bool BlueEngine::Engine::getMouseMode() {
    auto mouseMode = glfwGetInputMode(window, GLFW_CURSOR);
    if (mouseMode == GLFW_CURSOR_NORMAL) {
        return true;
    } else {
        return false;
    }
}

void BlueEngine::Engine::setMouseMode(bool mode) {
    if (mode == true) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

auto Engine::getIsRunning() const -> bool {
    return this->isRunning;
}

auto Engine::endEngine() -> void {
    isRunning = false;
}

auto Engine::getBasePath() -> void {
    // char *base_path = SDL_GetBasePath();
    // basepath        = std::string(base_path);
    // SDL_free(base_path);
    basepath = "./";
}
