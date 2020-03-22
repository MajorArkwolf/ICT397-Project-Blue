#include "Controller/InputManager.hpp"

#include <iostream>

#include <Controller/Engine/Engine.hpp>

namespace Controller::Input {
    InputManager &InputManager::getInstance() {
        static auto instance = InputManager{};

        return instance;
    }
    void InputManager::ProcessInput(SDL_Event &event) {
        // Handle input data from event
        InputData inputEvent;

        switch (event.type) {
            case SDL_KEYDOWN: {
                inputEvent.inputType = BLUE_InputType::KEY_PRESS;
            }; break;
            case SDL_KEYUP: {
                inputEvent.inputType = BLUE_InputType::KEY_RELEASE;
            }; break;
            case SDL_MOUSEMOTION: {
                inputEvent.inputType             = BLUE_InputType::MOUSE_MOTION;
                inputEvent.mouseMotionRelative.x = event.motion.xrel;
                inputEvent.mouseMotionRelative.y = event.motion.yrel;
                inputEvent.mouseMotionAbsolute.x = event.motion.x;
                inputEvent.mouseMotionAbsolute.y = event.motion.y;
            }; break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
            }; break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
            }; break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType        = BLUE_InputType::MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.wheel.y;
            }; break;
        }

        inputEvent.inputAction;

        for (auto itr : InputMap) {
            std::cout << int(itr.first) << ',' << int(itr.second) << std::endl;
        }
        // for (auto pair : InputMap) {
        //    // Looks through input map for action match with pressed key
        //    if (pair.second == event.key.keysym.scancode) {
        //        inputEvent.inputAction = pair.first;
        //        break;
        //    }
        //}

        // Send inputEvent to top of game stack or whatever
    }

    void InputManager::ReadBindings() {
        std::string basePath = "";

        char *base_path = SDL_GetBasePath();
        if (base_path) {
            basePath = std::string(base_path);
        } else {
            basePath = SDL_strdup("./");
        }

        SDL_free(base_path);
        auto &LuaManager = LuaManager::getInstance();

        auto luaState          = LuaManager.getLuaState();
        std::string scriptPath = basePath + "scripts/InputBindings.lua";
        if (luaL_dofile(luaState, scriptPath.c_str())) {
            std::cout << "No script file found at '" << scriptPath
                      << "', aborting input binding." << std::endl;
        } else {
            lua_pcall(luaState, 0, 0, 0);
            luaL_openlibs(luaState);
            luabridge::LuaRef table =
                luabridge::getGlobal(luaState, "InputBindings");
            if (!table.isNil()) {
                readLuaInputTable(table);
            }
        }
    }

    BLUE_InputDevice InputManager::hashInputValue(const std::string &value) {
        if (value == "LSHIFT") {
            return BLUE_InputDevice::KEY_LSHIFT;
        }
        if (value == "SPACE") {
            return BLUE_InputDevice::KEY_SPACE;
        }
        if (value == "A") {
            return BLUE_InputDevice::KEY_A;
        }

        return BLUE_InputDevice::UNKNOWN;

        // TODO Populate this list with value enum pairs
    }

    BLUE_InputDevice InputManager::SDLEventToBLUE(SDL_Event &event) {
        switch (event.type) {

            case SDL_MOUSEMOTION: {

            }; break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_0: {
                        return BLUE_InputDevice::KEY_0;
                    } break;
                    case SDL_SCANCODE_1: {
                        return BLUE_InputDevice::KEY_1;
                    } break;
                    case SDL_SCANCODE_2: {
                        return BLUE_InputDevice::KEY_2;
                    } break;
                    case SDL_SCANCODE_3: {
                        return BLUE_InputDevice::KEY_3;
                    } break;
                    case SDL_SCANCODE_4: {
                        return BLUE_InputDevice::KEY_4;
                    } break;
                    case SDL_SCANCODE_5: {
                        return BLUE_InputDevice::KEY_5;
                    } break;
                    case SDL_SCANCODE_6: {
                        return BLUE_InputDevice::KEY_6;
                    } break;
                    case SDL_SCANCODE_7: {
                        return BLUE_InputDevice::KEY_7;
                    } break;
                    case SDL_SCANCODE_8: {
                        return BLUE_InputDevice::KEY_8;
                    } break;
                    case SDL_SCANCODE_9: {
                        return BLUE_InputDevice::KEY_9;
                    } break;
                    case SDL_SCANCODE_A: {
                        return BLUE_InputDevice::KEY_A;
                    } break;
                    case SDL_SCANCODE_B: {
                        return BLUE_InputDevice::KEY_B;
                    } break;
                    case SDL_SCANCODE_C: {
                        return BLUE_InputDevice::KEY_C;
                    } break;
                    case SDL_SCANCODE_D: {
                        return BLUE_InputDevice::KEY_D;
                    } break;
                    case SDL_SCANCODE_E: {
                        return BLUE_InputDevice::KEY_E;
                    } break;
                    case SDL_SCANCODE_F: {
                        return BLUE_InputDevice::KEY_F;
                    } break;
                    case SDL_SCANCODE_G: {
                        return BLUE_InputDevice::KEY_G;
                    } break;
                    case SDL_SCANCODE_H: {
                        return BLUE_InputDevice::KEY_H;
                    } break;
                    case SDL_SCANCODE_I: {
                        return BLUE_InputDevice::KEY_I;
                    } break;
                    case SDL_SCANCODE_J: {
                        return BLUE_InputDevice::KEY_J;
                    } break;
                    case SDL_SCANCODE_K: {
                        return BLUE_InputDevice::KEY_K;
                    } break;
                    case SDL_SCANCODE_L: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_M: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_N: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_O: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_P: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_Q: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_R: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_S: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_T: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_U: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_V: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_W: {
                        return BLUE_InputDevice::KEY_L;
                    } break;
                    case SDL_SCANCODE_X: {
                        return BLUE_InputDevice::KEY_L;
                    } break;

                }
            } break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL: {

            }; break;
        }
    }

    void InputManager::bindKey(BLUE_InputAction action,
                               luabridge::LuaRef &inputTable, std::string value) {

        luabridge::LuaRef inputRef = inputTable[value];

        if (inputRef.isString()) {
            std::string input = inputRef.cast<std::string>();
            std::cout << input << std::endl;
            InputMap.insert(std::pair<BLUE_InputAction, BLUE_InputDevice>(
                action, hashInputValue(input)));
        }
    }

    void InputManager::bindKey(BLUE_InputAction, BLUE_InputDevice) {}

    void InputManager::readLuaInputTable(luabridge::LuaRef inputTable) {

        bindKey(BLUE_InputAction::INPUT_JUMP, inputTable, "JUMP");
        bindKey(BLUE_InputAction::INPUT_SPRINT, inputTable, "SPRINT");
    }

    void InputManager::DefaultInputMap() {
        InputMap.at(BLUE_InputAction::INPUT_JUMP) = BLUE_InputDevice::KEY_SPACE;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_FORWARD) = BLUE_InputDevice::KEY_W;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_BACKWARD) = BLUE_InputDevice::KEY_S;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_LEFT) = BLUE_InputDevice::KEY_A;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_RIGHT) = BLUE_InputDevice::KEY_D;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_1) = BLUE_InputDevice::MOUSE_LEFT;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_2) =
            BLUE_InputDevice::MOUSE_RIGHT;
        InputMap.at(BLUE_InputAction::INPUT_SPRINT) = BLUE_InputDevice::KEY_LSHIFT;
        InputMap.at(BLUE_InputAction::INPUT_CROUCH) = BLUE_InputDevice::KEY_LCTRL;
    }

    InputManager::~InputManager() {}
    InputManager::InputManager() {}
}
