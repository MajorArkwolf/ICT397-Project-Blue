#include "Controller/Engine/Engine.hpp"

#include <iostream>
#include <stdexcept>

#include "Controller/PhysicsFacade/React/ReactShapes.hpp"

// Game States
#include "Game/Prototype/PrototypeScene.hpp"

using BlueEngine::Engine;
using std::runtime_error;
using std::string;

auto Engine::run() -> void {
    auto &engine = Engine::get();

    ResourceManager::getInstance().loadResources();
    engine.gameStack.AddToStack(std::make_shared<PrototypeScene>());

    double t  = 0.0;
    double dt = 0.01;

    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    // State previous;
    // State current;
    // State state;
    // glfwFocusWindow(engine.window);
    engine.renderer.Init();


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

        // const double alpha = accumulator / dt;
        // state = currentState * alpha + previousState * (1.0 - alpha);

        engine.gameStack.getTop()->display();
        engine.renderer.Draw();
    }
    glfwDestroyWindow(engine.window);
}

GUIManager &BlueEngine::Engine::getGuiManager() {
    return guiManager;
}

Engine::Engine(){
    getBasePath();
    if (!glfwInit()) {
        std::cerr << "GLFW FAILED TO INIT \n";
    }
    gleqInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width / 2, mode->height / 2, "Project Blue", nullptr, nullptr);
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

}

Engine::~Engine() {
    glfwTerminate();
}

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
    return mouseMode == GLFW_CURSOR_NORMAL;
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
