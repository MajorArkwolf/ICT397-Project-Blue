#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "glm/vec2.hpp"

namespace Controller {
    namespace Input {

        using Controller::MethodResult;

        struct InputData {
            glm::ivec2 mouseMotionRelative = {0, 0};
            glm::ivec2 mouseMotionAbsolute = {0, 0};
            float mouseWheelMotion         = 0.f;
            enum BLUE_Input inputAction;
            enum BLUE_InputType inputType;
        };

        class InputManager {
          public:

            static InputManager *getInstance() {
                static InputManager instance;
                return &instance;
            }
            MethodResult ProcessInput(SDL_Event &event);

            MethodResult
            MapInputs(std::vector<std::pair<BLUE_Input, SDL_Scancode>> &mappings);

          private:
            std::vector<std::pair<BLUE_Input, SDL_Scancode>>
                InputMap; // A vector of pairs linking a BLUE_Input and an SDL_Keycode, vector index corresponds to BLUE_Input enum number.
            InputManager();
            ~InputManager();
            InputManager(const InputManager &other) = delete;
            InputManager operator=(InputManager &rhs) = delete;
        };
    }
}
