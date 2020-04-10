#include "Controller/Engine/Engine.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "BaseState.hpp"
#include "GameStack.hpp"

#include "Controller/InputManager.hpp"
#include "Controller/GUIManager.hpp"


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
            //engine.processInput();
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
    // Start SDL.
    if (!glfwInit()) {
        std::cerr << "GLFW FAILED TO INIT \n";
    }
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
    window = glfwCreateWindow(800, 600, "Project Blue", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Engine::mouse_callback);
    glfwSetScrollCallback(window, Engine::scroll_callback);

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

//auto Engine::processInput() -> void {
    //auto event        = SDL_Event{};
    //auto handledMouse = true;
    //auto &inputManager = Controller::Input::InputManager::getInstance();

    //while (SDL_PollEvent(&event)) {
    //    if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.type == SDL_KEYDOWN) {
    //        relativeMouseMode = relativeMouseMode ? SDL_FALSE : SDL_TRUE;
    //        SDL_SetRelativeMouseMode(relativeMouseMode);
    //    }
    //    ImGui_ImplSDL2_ProcessEvent(&event);
    //    gameStack.getTop()->handleInputData(inputManager.ProcessInput(event));
    //}
    //if (!handledMouse) {
    //    this->mouse = {0.0f, 0.0f};
    //}
//}

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

void Engine::processInput(GLFWwindow *window) {
    auto &engine = BlueEngine::Engine::get();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Engine::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    auto &engine = BlueEngine::Engine::get();
    if (engine.firstMouse) {
        engine.lastX      = xpos;
        engine.lastY      = ypos;
        engine.firstMouse = false;
    }

    float xoffset = xpos - engine.lastX;
    float yoffset = engine.lastY - ypos; // reversed since y-coordinates go from bottom to top

    engine.lastX = xpos;
    engine.lastY = ypos;
    //camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Engine::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //camera.ProcessMouseScroll(yoffset);
}