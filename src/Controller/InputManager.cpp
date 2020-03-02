#include "InputManager.hpp"

namespace Controller::Input {

    MethodResult InputManager::ProcessInput(SDL_Event &event) {

        assert(!InputMap.empty());
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
            }; break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = MOUSE_BUTTONDOWN;
            }; break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = MOUSE_BUTTONUP;
            }; break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType = MOUSE_WHEEL;
            }; break;
        }

        for (auto pair : InputMap) { //
            if (pair.second == event.key.keysym.scancode) {
                inputEvent.input = pair.first;
                break;
            }
        }

        // Send to top of game stack

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