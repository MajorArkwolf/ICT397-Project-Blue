#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "glm/vec2.hpp"

namespace Controller {
    namespace Input {

        using Controller::MethodResult;

        struct InputData{
            glm::vec2 mouseMotion  = {0, 0};
            float mouseWheelMotion = 0.f;
            BLUE_Input input;
            BLUE_InputType inputType;
        } ;

        enum BLUE_Input {
            INPUT_DEFAULT,
            INPUT_JUMP,
            INPUT_MOVE_FORWARD,
            INPUT_MOVE_BACKWARD,
            INPUT_MOVE_LEFT,
            INPUT_MOVE_RIGHT,
            INPUT_LOOK_UP,
            INPUT_LOOK_DOWN,
            INPUT_LOOK_LEFT,
            INPUT_LOOK_RIGHT,
            INPUT_ACTION_1,
            INPUT_ACTION_2,
            INPUT_ACTION_3,
            INPUT_ACTION_4
        };

        enum BLUE_InputType {
            KEY_DOWN,
            KEY_RELEASE,
            MOUSE_MOTION,
            MOUSE_WHEEL,
            MOUSE_BUTTONDOWN,
            MOUSE_BUTTONUP
        };

        class InputManager {
          public:

            MethodResult ProcessInput(SDL_Event &event);

            MethodResult
            MapInputs(std::vector<std::pair<BLUE_Input, SDL_Scancode>> mappings);

          private:
            std::vector<std::pair<BLUE_Input, SDL_Scancode>>
                InputMap; // A vector of pairs linking a BLUE_Input and an SDL_Keycode, vector index corresponds to BLUE_Input enum number.
        };
    }
}