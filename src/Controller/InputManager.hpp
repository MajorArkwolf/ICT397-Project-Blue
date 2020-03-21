#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "glm/vec2.hpp"
#include "Engine/Engine.hpp"

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
            static InputManager *getInstance() {
                static InputManager instance;
                return &instance;
            }
            void ProcessInput(SDL_Event &event);
            void ReadBindings();
            void DefaultInputMap();

          private:
            std::map<BLUE_InputAction, BLUE_InputDevice> InputMap;
            void readLuaInputTable(luabridge::LuaRef inputTable);
            void bindKey(BLUE_InputAction, luabridge::LuaRef &inputTable,
                    std::string value);
            BLUE_InputDevice hashInputValue(const std::string &value);

            InputManager();
            ~InputManager();
            InputManager(const InputManager &other) = delete;
            InputManager operator=(InputManager &rhs) = delete;
        };
    }
}
