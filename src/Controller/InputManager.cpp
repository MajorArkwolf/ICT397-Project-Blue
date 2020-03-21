#include "Controller/InputManager.hpp"
#include <iostream>

namespace Controller::Input {

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
        auto &LuaManager    = LuaManager::getInstance();
        auto luaState   = LuaManager.getLuaState();
        std::string scriptPath = "scripts/InputBindings.lua";
        if (luaL_dofile(luaState, scriptPath.c_str()) ||
            lua_pcall(luaState, 0, 0, 0)) {
            std::cout << "No script file found at '" << scriptPath
                      << "', aborting binding." << std::endl;
        }

        luaL_openlibs(luaState);
        luabridge::LuaRef table =
            luabridge::getGlobal(luaState, "InputBindings");
        if (!table.isNil()) {
            readLuaInputTable(table);
        }

        std::cout << int(InputMap.at(BLUE_InputAction::INPUT_JUMP)) << std::endl;
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

    void InputManager::bindKey(BLUE_InputAction action,
                               luabridge::LuaRef &inputTable, std::string value) {

        luabridge::LuaRef inputRef = inputTable[value];

        if (inputRef.isString()) {
            std::string input   = inputRef.cast<std::string>();
            InputMap.at(action) = hashInputValue(input);
        }
    }

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
}
