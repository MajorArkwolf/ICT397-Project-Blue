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
                inputEvent.inputType             = MOUSE_MOTION;
                inputEvent.mouseMotionRelative.x = event.motion.xrel;
                inputEvent.mouseMotionRelative.y = event.motion.yrel;
                inputEvent.mouseMotionAbsolute.x = event.motion.x;
                inputEvent.mouseMotionAbsolute.y = event.motion.y;
            }; break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = MOUSE_BUTTONDOWN;
            }; break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = MOUSE_BUTTONUP;
            }; break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType        = MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.wheel.y;
            }; break;
        }

        for (auto pair :
             InputMap) { // Looks through input map for action match with pressed key
            if (pair.second == event.key.keysym.scancode) {
                inputEvent.inputAction = pair.first;
                break;
            }
        }



        // Send inputEvent to top of game stack or whatever

        bool inputProcessed = (inputEvent.inputAction != BLUE_Input::INPUT_DEFAULT);
        if (inputProcessed) {
            return MethodResult::METHOD_SUCCESS;
        } else {
            return MethodResult::METHOD_FAILURE;
        }
    }

    MethodResult InputManager::MapInputs(
        std::vector<std::pair<BLUE_Input, SDL_Scancode>> &mappings) {
        InputMap = mappings;
        return MethodResult::METHOD_SUCCESS;
    }

    InputManager::~InputManager() {}
    //THIS IS A STUB
}
