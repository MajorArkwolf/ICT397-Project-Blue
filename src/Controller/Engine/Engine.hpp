#pragma once

#include <memory>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLEQ_IMPLEMENTATION
#define GLEQ_STATIC
#include "gleq.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "BaseState.hpp"
#include "Controller/Physics/BeRP3DFactory.hpp"
#include "Controller/Physics/BePhysicsLibrary.hpp"
#include "Controller/GUIManager.hpp"
#include "Controller/ResourceManager.hpp"
#include "GameStack.hpp"
#include "View/Renderer/OpenGL.hpp"

constexpr unsigned int SCR_WIDTH  = 800;
constexpr unsigned int SCR_HEIGHT = 600;

namespace BlueEngine {
    class Engine {
      public:
        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /// Mouse movement.
        glm::vec2 mouse = {};

        /// GLFW handles.
        GLFWwindow *window = nullptr;

        /// Renderer for OpenGL
        View::OpenGL renderer = {};

        /// The current FPS
        double fps           = 0.0;
        /// Base path to the program.
        std::string basepath = "";

      private:
        /// The game stack to allow to switch between scenes.
        GameStack<std::shared_ptr<BaseState>> gameStack;
        /// GUI Manager for our GUI interface.
        GUIManager guiManager;
        /// Flag used to determine if the engine should shutdown.
        bool isRunning = true;
        /**
         * Gets the basepath of where the engine is running.
         */
        auto getBasePath() -> void;
        /**
         * Privatised constructor due to the engine being a singleton.
         */
        Engine();

        /// Testing values
        float lastX     = SCR_WIDTH / 2.0f;
        float lastY     = SCR_HEIGHT / 2.0f;
        bool firstMouse = true;

        //Testing physics delete after
        static inline double factor = 0.00;
        static inline uint64_t prevTime = 0;
        static inline double timeStep = 1.0 / 60.0;
        static inline double acc = 0.0;

      public:
        /**
         * Deleted move constructor due to unique pointers being used.
         */
        Engine(Engine &&)      = delete;

        /**
         * Deleted move destructor due to unique pointers being used.
         */
        Engine(const Engine &) = delete;

        /**
         * Destructor for the engine
         */
        ~Engine();

        /**
         * @brief Getter to the engine variables.
         * @return Engine by reference
         */
        static auto get() -> Engine &;

        /**
         * @brief The game engine main loop
         */
        static auto run() -> void;

        /**
         * Gets the GUI manager interface.
         * @return the GUIManager object.
         */
        GUIManager &getGuiManager();

        /**
         * @brief Overloaded assignment operator, set to default overload
         */
        auto operator=(Engine &&) -> Engine & = delete;

        /**
         * @brief Overloaded const assignment operator, set to delete overload
         */
        auto operator=(const Engine &) -> Engine & = delete;

        /**
         * Check to see if the engine is running.
         * @return the current state of the engine.
         */
        auto getIsRunning() const -> bool;

        /**
         * Tells the engine the program is requesting termination.
         */
        auto endEngine() -> void;

        /**
         * Process the input from our 3rd party library.
         */
        void processInput();

        /**
         * Checks to see what type of mouse mode the engine has set.
         * @return the value of the mouse.
         */
        bool getMouseMode();

        /**
         * Sets the mouse mode
         * @param mode sets the mouse mode.
         */
        void setMouseMode(bool mode);
    };
}
