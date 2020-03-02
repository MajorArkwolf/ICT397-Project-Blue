#include "InputManager.hpp"

namespace Controller::Input {

    MethodResult InputManager::ProcessInput(SDL_Event &event) {
        // Handle input data from event
        InputData inputEvent;

        switch (event.type) {
            case SDL_KEYDOWN: {
                inputEvent.inputType = KEY_DOWN;
            }; break;
            case SDL_KEYUP: {
                inputEvent.inputType = KEY_RELEASE;
            }; break;
            case SDL_MOUSEMOTION: {
                inputEvent.inputType = MOUSE_MOTION;
                inputEvent.mouseMotion.x = event.motion.xrel;
                inputEvent.mouseMotion.y = event.motion.yrel;
            }; break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = MOUSE_BUTTONDOWN;
            }; break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = MOUSE_BUTTONUP;
            }; break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType = MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.wheel.y;
            }; break;
        }

        for (auto pair : InputMap) { //Looks through input map for action match with pressed key
            if (pair.second == event.key.keysym.scancode) {
                inputEvent.inputAction = pair.first;
                break;
            }
        }


        // Send inputEvent to top of game stack or whatever

        if (1 /*If data handled , return success*/) {
            return MethodResult::METHOD_SUCCESS;
        } else {
            return MethodResult::METHOD_FAILURE;
        }
    }

    MethodResult InputManager::MapInputs(
        std::vector<std::pair<BLUE_Input, SDL_Scancode>> mappings) {
        InputMap = mappings;
        return MethodResult::METHOD_SUCCESS;
    }

}
