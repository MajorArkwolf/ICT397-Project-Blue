#include "Controller/Engine/Engine.hpp"
#include "Controller/InputManager.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "BaseState.hpp"
#include "GameStack.hpp"

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

    double currentTime = engine.getTime();
    double accumulator = 0.0;

    //State previous;
    //State current;
    //State state;

    while (engine.getIsRunning()) {
        double newTime   = engine.getTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt) {
            //previousState = currentState;
            engine.processInput();
            engine.gameStack.getTop()->update(t, dt);
            t += dt;
            accumulator -= dt;
        }
        const double alpha = accumulator / dt;
        //state = currentState * alpha + previousState * (1.0 - alpha);

        engine.gameStack.getTop()->display();
    }
}

/**
 * @brief Game engine default constructor, sets up all variables and settings required for operation
 */
Engine::Engine() {
    // Start SDL.
    auto status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (status != 0) {
        throw runtime_error{string{"Unable to initialize SDL: "} + SDL_GetError()};
    }

    // Set OpenGL settings.
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
#else
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif

    // Get display size.
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);

    // Create window.
    this->window = Engine::Window{
        SDL_CreateWindow("Project-Blue", display.w / 4, display.h / 4,
                         display.w / 2, display.h / 2,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI),
        &SDL_DestroyWindow};

    if (this->window.get() == nullptr) {
        throw runtime_error{string{"Unable to create window: "} + SDL_GetError()};
    }

    // Create OpenGL context.
    this->context = Engine::Context{SDL_GL_CreateContext(this->window.get()),
                                    &SDL_GL_DeleteContext};

    if (this->context.get() == nullptr) {
        throw runtime_error{string{"Unable to create OpenGL context: "} +
                            SDL_GetError()};
    }

    SDL_GL_MakeCurrent(this->window.get(), this->context.get());

    // Enable Vsync.
    constexpr auto ENABLE_VSYNC = 0;
    SDL_GL_SetSwapInterval(ENABLE_VSYNC);

    // Capture the mouse.
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Check OpenGL properties
    // std::cout << "OpenGL loaded\n";
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    luaState = luaL_newstate();
}

/**
 * @brief Engine default destructor
 * Safely closes Engine and frees memory
 */
Engine::~Engine() {
    SDL_Quit();
}

auto BlueEngine::Engine::getLuaState() -> lua_State* {
    if (luaState != nullptr) {
        return luaState;
    } else {
        luaState = luaL_newstate();
        return luaState;
    }
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
    auto event  = SDL_Event{};
    auto handledMouse = true;

    while (SDL_PollEvent(&event)) {
        gameStack.getTop()->handleInput(event);
    }
    if (!handledMouse) {
        this->mouse = {0.0f, 0.0f};
    }
}

auto Engine::getIsRunning() const -> bool {
    return this->isRunning;
}

auto Engine::endEngine() -> void {
    isRunning = false;
}

/**
 * @brief I DONT KNOW WHAT THIS DOES
 * @return What is this
 */
auto Engine::getTime() const -> double {
    return static_cast<double>(SDL_GetPerformanceCounter()) /
           static_cast<double>(SDL_GetPerformanceFrequency());
}

auto Engine::getBasePath() -> std::string {
    if (basepath == "") {
        char *base_path = SDL_GetBasePath();
        basepath        = std::string(base_path);
        SDL_free(base_path);
    }
    return basepath;

}
