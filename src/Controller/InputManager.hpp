#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include <glm/vec2.hpp>
#include <map>

#include "Controller/Enums.hpp"
#include "Controller/Engine/LuaManager.hpp"

namespace Controller {
    namespace Input {

        using Controller::MethodResult;

        struct InputData {
            glm::ivec2 mouseMotionRelative = {0, 0};
            glm::ivec2 mouseMotionAbsolute = {0, 0};
            float mouseWheelMotion         = 0.f;
            BLUE_InputAction inputAction;
            BLUE_InputType inputType;
        };

        class InputManager {
          public:
            static InputManager &getInstance();
            InputData ProcessInput(SDL_Event &event);
            void ReadBindings();
            void DefaultInputMap();

          private:
            std::map<BLUE_InputAction, SDL_Scancode> InputMap;
            void readLuaInputTable(luabridge::LuaRef inputTable);
            void bindKey(BLUE_InputAction, luabridge::LuaRef &inputTable,
                    std::string value);
            void bindKey(BLUE_InputAction, SDL_Scancode);
            SDL_Scancode hashInputValue(const std::string &value);

            InputManager();
            ~InputManager();
            InputManager(const InputManager &other) = delete;
            InputManager operator=(InputManager &rhs) = delete;
            void populateInputMap();
        };
    }
}
