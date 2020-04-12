#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>

#define GLEQ_IMPLEMENTATION
#define GLEQ_STATIC
#include "gleq.h"
//
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "BaseState.hpp"
#include "Controller/GUIManager.hpp"
#include "Controller/ResourceManager.hpp"
#include "GameStack.hpp"

const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

namespace BlueEngine {
    class Engine {
      public:
        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* GLFW handles. */
        GLFWwindow *window = nullptr;

        /**
         * @brief The current FPS
         */
        double fps           = 0.0;
        std::string basepath = "";

      private:
        GameStack<BaseState *> gameStack;
        GUIManager guiManager;
        bool isRunning = true;
        auto getBasePath() -> void;
        Engine();

        /// Testing values
        float lastX     = SCR_WIDTH / 2.0f;
        float lastY     = SCR_HEIGHT / 2.0f;
        bool firstMouse = true;

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
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

        GUIManager &getGuiManager();
        /**
         * @brief Overloaded assignment operator, set to default overload
         */
        auto operator=(Engine &&) -> Engine & = default;

        /**
         * @brief Overloaded const assignment operator, set to delete overload
         */
        auto operator=(const Engine &) -> Engine & = delete;

        auto getIsRunning() const -> bool;

        auto endEngine() -> void;

        void processInput();

        bool getMouseMode();

        void setMouseMode(bool mode);

    };
}
