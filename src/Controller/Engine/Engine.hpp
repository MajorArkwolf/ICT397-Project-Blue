#pragma once

#include <SDL.h>
#include <memory>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "BaseState.hpp"
#include "Controller/GUIManager.hpp"
#include "Controller/ResourceManager.hpp"
#include "GameStack.hpp"

namespace BlueEngine {
    class Engine {
      public:
        using Window  = std::shared_ptr<SDL_Window>;
        using Context = std::shared_ptr<void>;

        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* SDL handles. */
        Window window   = nullptr;
        Context context = nullptr;

        /**
         * @brief The current FPS
         */
        double fps           = 0.0;
        std::string basepath = "";

        auto getTime() const -> double;

        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        // This variable will hold the game stack
        // Game *thegame = nullptr;

        static auto get() -> Engine &;
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

        auto processInput() -> void;

      private:
        GameStack<BaseState *> gameStack;
        GUIManager guiManager;
        bool isRunning             = true;
        SDL_bool relativeMouseMode = SDL_TRUE;

        auto getBasePath() -> void;

        Engine();
    };
}
